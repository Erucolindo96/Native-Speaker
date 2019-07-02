#ifndef MFCCCONVERTER_HPP
#define MFCCCONVERTER_HPP
#include<alize.h>
#include<string>
#include"exceptions/simple_exceptions.hpp"
#include<cstdlib>
#include<unistd.h>
#include<thread>
#include<sys/wait.h>
#include<QProcess>
#include"utils/utils.hpp"

#include"features/SPro4File.hpp"
/**
 * @brief The MfccConverter Klasa, która przetwarza plik dźwiękowy
 * na wektory cech w formacie SPro4
 * Klasy pochodne implementują sposób konwersji poszczególnych formatów dźwiękowych.
 */
class MfccConverter
{

public:
  const uint32_t DEF_SAMPLE_RATE_= 8000, DEF_FRAME_LENGHT_ = 20, DEF_INTERVAL_ = 10,
  DEF_FEATURE_LENGHT_ = 12;
  const double DEF_PRE_EMPHASIS_ = 0.95;
  const bool DEF_WITH_LOG_ENERGY_ = true,
  DEF_WITH_DIFF_VEC_ = true;

  MfccConverter();
  MfccConverter(const MfccConverter &other) = default;
  MfccConverter& operator=(const MfccConverter &other) = default;
  MfccConverter(MfccConverter &&other) = default;
  MfccConverter& operator=(MfccConverter &&other) = default;
  virtual ~MfccConverter() = default;
  /**
   * @brief convertToSPro4 Przetwarza dane nagranie do postaci wektorów cech Mfcc,
   * i zwraca uchwyt do pliku, zawierającego wynikowe wektory cech
   * @param source_record Nagranie, które chcemy przetworzyć.
   * Klasy dziedziczące implementują konwersję dla konkretnych formatów nagrań
   * @return Uchwyt do pliku w formacie SPro4, zawierającego wektory cech po przetworzeniu
   * @throw FileNotFound Jesli plik wskazywany przez source_record nie istnieje
   * @throw UnableToConvertToMfcc Jesli program konwertujący zawodzi
   */
  virtual SPro4File convertToSPro4(const Record &source_record)const = 0;

  /**
   * @brief setSampleRate Ustawia częstotliwośc próbkowania sygnału
   * @param sample_rate Częstotliwość próbkowania nagrania w herz'ach
   * @throw std::invalid_argument jesli sample_rate nie jest dodatnie
   */
  void setSampleRate(int32_t sample_rate);
  uint32_t getSampleRate()const;
  /**
   * @brief setPreEmphasis Ustawia pre-emphasis coefficient
   * @param pre_emphasis Wartośc współczynnika
   * @throw std::invalid_argument Jeśli pre_emphasis większy od 0.95 lub kiedy jest niedodatki
   */
  void setPreEmphasis(double pre_emphasis);
  double getPreEmphasis()const;

  /**
   * @brief setFrameLenght Ustawia długość ramki, z której będzie generowany 1 wektor cech
   * @param frame_lenght Długość ramki w milisekundach
   * @throw std::invalid_argument jeśli frame_lenght niedodatnie
   */
  void setFrameLenght(int32_t frame_lenght);
  uint32_t getFrameLenght()const;

  /**
   * @brief setInterval Ustawia odległość między kolejnymi ramkami
   * @param interval Odległość pomiędzy ramkami w milisekundach
   * @throw std::invalid_argument jeśli interval niedodatnie
   */
  void setInterval(int32_t interval);
  uint32_t getInterval()const;

  /**
   * @brief setFeatureLenght Ustawia długość uzyskiwanego wektora cech z jednej ramki sygnału
   * Nie może być większa niż 24.
   * Ponadto jest to tylko długość wektora cech - nie bierze pod uwagę logarytmu energii danej ramki sygnału. Jest on dodawany metodą setLogEnergy();
   * @param f_lenght Długość jednego wektora cech
   * @throw std::invalid_argument jeśli f_lenght niedodatnie lub większe niż 24
   */
  void setFeatureLenght(int32_t f_lenght);

  /**
   * @brief setLogEnergy Określa, czy do wektora cech powinien być dodany logarytm energii danej ramki.
   * Zwiększa do długość wynikowego wektora cech o 1 element
   * @param yes True jeśli log energii ma być dodany, false w przeciwnym razie
   */
  void setLogEnergy(bool yes);

  /**
   * @brief setFirstOrderDerivative Określa, czy do wektora cech powinien być dodany wektor różnicowy
   * będący różnicą wartości wektorów poprzedniego i następnego(chyba).
   * Jeżeli do wektora cech dodawany jest logarytm energii, to, w przypadku dodawania wektora róznicowego
   * również na końcu wektora różnicowego będzie dodawana różnica energii
   * @param yes True jeśli wektor różnicowy ma być dodany, false w przeciwnym razie
   */
  void setFirstOrderDerivative(bool yes);


  /**
   * @brief getFeatureLenght Zwraca długość wynikowego wektora cech, po konwersji.
   * Przy obliczaniu długości brany jest pod uwagę logarytm energii w wektorze cech,
   * oraz obecność lub brak wektora różnicowego
   * @return Całkowita długość wynikowego wektora cech
   */
  uint32_t getFeatureLenght()const;

protected:
  uint32_t sample_rate_, frame_lenght_, interval_, f_lenght_;
  double pre_emphasis_;
  bool with_log_energy_, with_diff_vec_;
  const uint32_t log_energy_scale_factor_ = 1;


};
/**
 * @brief The MfccConverterWav class Klasa zdolna konwertować pliki w formacie .wav.
 * W konstruktorze domyślnym ustawiane są parametry konwersji, dedykowane do pliku w formacie .wav o częstotliwości próbkowania 48kHz.
 * Wynikowy wektor cech ma 24 elementy, oraz dodany na końcu wektora logarytm energii
 */
class MfccConverterWav: public MfccConverter
{
public:
  /**
   * @brief MfccConverterWav Ustawia parametry konwersji, pasujące do pliku .wav o częstotliwości próbkowania 48kHz
   */
  MfccConverterWav();
  MfccConverterWav(const MfccConverterWav &other) = default;
  MfccConverterWav& operator=(const MfccConverterWav &other) = default;
  MfccConverterWav(MfccConverterWav &&other) = default;
  MfccConverterWav& operator=(MfccConverterWav &&other) = default;
  ~MfccConverterWav() override = default;

  /**
   * @brief convertToSPro4 Przetwarza dane nagranie do postaci wektorów cech Mfcc,
   * i zwraca uchwyt do pliku, zawierającego wynikowe wektory cech
   * @param source_record Nagranie, które chcemy przetworzyć.
   * Musi być to nagranie w formacie WAV, inaczej konwersja się nie powiedzie
   * @return Uchwyt do pliku w formacie SPro4, zawierającego wektory cech po przetworzeniu
   * @throw FileNotFound Jesli plik wskazywany przez source_record nie istnieje
   * @throw UnableToConvertToMfcc Jesli program konwertujący zawodzi lub nie można skonwertować danego formatu pliku
   */
  SPro4File convertToSPro4(const Record &source_record)const override;
protected:
  QStringList setArgumentsToSfbcep(const QString &source_file, const QString &dest_file)const;
  QStringList setArgumentsToSox(const QString &source_file, const QString &dest_file)const;


};

//class MfccConverterLinux
//{
//protected:
//  const std::string CONVERT_SCRIPT_PATH = "./scripts/convert_mp3_to_SPro4.sh";
//public:
//  MfccConverterLinux() = default;
//  MfccConverterLinux(const MfccConverterLinux &other) = default;
//  MfccConverterLinux& operator=(const MfccConverterLinux &other) = default;
//  MfccConverterLinux(MfccConverterLinux &&other) = default;
//  MfccConverterLinux& operator=(MfccConverterLinux &&other) = default;

//  int32_t runMadPlay(const std::string &source_dir,const std::string &source_name,
//                  const std::string &dest_dir,const std::string &dest_name)const;
//  int32_t runSfbcep(const std::string &source_dir,const std::string &source_name,
//                    const std::string &dest_dir,const std::string &dest_name)const;
//  virtual void convertToSPro4(const std::string &source_path,
//                              const std::string &dest_dir,const std::string &dest_name)const ;

//};


#endif // MFCCCONVERTER_HPP
