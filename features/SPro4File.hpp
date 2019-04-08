#ifndef SPRO4FILE_HPP
#define SPRO4FILE_HPP

#include"record-base/Record.hpp"

class SPro4File: public Record
{
public:
  static const QString VALID_EXT;

  SPro4File()=default;
  SPro4File(const SPro4File &other)=default;
  SPro4File& operator=(const SPro4File &other)=default;
  SPro4File(SPro4File &&other)=default;
  SPro4File& operator=(SPro4File &&other)=default;
  ~SPro4File() override = default;
  /**
   * @brief setPath Ustawia ścieżkę do pliku z nagraniem, wskazywanego przez klasę
   * @param rec_path Scieżka do nagrania
   * @throw FileNotFound jeśli nie można znaleźć pliku określonego daną ścieżką
   * @throw NotASProFile jeśli plik o danej ścieżce nie jest plikiem z rozszerzeniem VALID_MFCC
   * @see SPro4File::VALID_EXT
   */
  void setPath(const QString &rec_path) override;
  /**
   * @brief setPath Ustawia ścieżkę do pliku z nagraniem, wskazywanego przez klasę
   * @param rec_name pełna nazwa pliku
   * @param rec_dir folder, w którym znajduje się nagranie
   * @throw FileNotFound jeśli w danym folderze nie ma nagrania o danej nazwie
   * @throw DirNotFound jeśli wskazany jako parametr folder nie istnieje
   * @throw NotASProFile jeśli plik o danej ścieżce nie jest plikiem z rozszerzeniem VALID_MFCC
   * @see SPro4File::VALID_EXT
   */
  void setPath(const QString &rec_name, const QDir &rec_dir) override;

  /**
   * @brief getRecordInfo Zwraca informację o nagraniu wskazywanym przez klasę
   * @return Informację o nagraniu wskazywanym przez klasę
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   * @throw NotASProFile jeśli plik wskazywany przez klasę nie jest plikiem z rozszerzeniem VALID_MFCC
   * @see SPro4File::VALID_EXT
   */
  QFileInfo getRecordInfo()const override;

  /**
   * @brief copy Kopiuje nagranie wskazywane przez klasę do folderu podanego jako parametr
   * @param dest_dir Folder, do którego zostanie skopiowane nagranie
   * @return Odnośnik do kopii nagrania
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   * @throw DirNotFound jeśli wskazany jako parametr folder nie istnieje
   * @throw NotASProFile jeśli plik wskazywany przez klasę nie jest plikiem z rozszerzeniem VALID_MFCC
   * @see SPro4File::VALID_EXT
   */
  SPro4File copy(const QDir &dest_dir)const;

  std::unique_ptr<MfccConverter> getConverter()const = delete;

protected:
  explicit SPro4File(const Record &rec);
  void validate()const;

};

#endif // SPRO4FILE_HPP
