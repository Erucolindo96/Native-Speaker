#ifndef RECORD_HPP
#define RECORD_HPP

#include"exceptions/simple_exceptions.hpp"
#include<memory>
#include<QFileInfo>

#include<QDir>

  class MfccConverter;
  class MfccConverterWav;
/**
 * @brief The Record class Służy jako reprezentacja uchwytu do pliku z nagraniem.
 * Nie przechowuje samego nagrania w pamięci, lecz posiada ścieżkę do pliku w filesystemie
 */
class Record
{

public:

  Record() = default;
  Record(const Record &other) = default;
  Record& operator=(const Record &other) = default;
  Record(Record &&other) = default;
  Record& operator=(Record &&other) = default;
  virtual ~Record() = default;
  /**
   * @brief setPath Ustawia ścieżkę do pliku z nagraniem, wskazywanego przez klasę
   * @param rec_path Scieżka do nagrania
   * @throw FileNotFound jeśli nie można znaleźć pliku określonego daną ścieżką
   */
  virtual void setPath(const QString &rec_path);
  /**
   * @brief setPath Ustawia ścieżkę do pliku z nagraniem, wskazywanego przez klasę
   * @param rec_name pełna nazwa pliku
   * @param rec_dir folder, w którym znajduje się nagranie
   * @throw FileNotFound jeśli w danym folderze nie ma nagrania o danej nazwie
   * @throw DirNotFound jeśli wskazany jako parametr folder nie istnieje
   */
  virtual void setPath(const QString &rec_name, const QDir &rec_dir);

  /**
   * @brief getRecordInfo Zwraca informację o nagraniu wskazywanym przez klasę
   * @return Informację o nagraniu wskazywanym przez klasę
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   */
  virtual QFileInfo getRecordInfo()const;

  /**
   * @brief copy Kopiuje nagranie wskazywane przez klasę do folderu podanego jako parametr
   * @param dest_dir Folder, do którego zostanie skopiowane nagranie
   * @return Odnośnik do kopii nagrania
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   * @throw DirNotFound jeśli wskazany jako parametr folder nie istnieje
   */
  Record copy(const QDir &dest_dir)const;
  /**
   * @brief move Przemieszcza nagranie wskazywane przez klasę do innego folderu
   * @param dest_dir Folder, do którego zostanie przeniesione nagranie
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   * @throw DirNotFound jeśli wskazany jako parametr folder nie istnieje
   */
  void move(const QDir &dest_dir);

  /**
   * @brief rename Zmienia nazwę nagrania na inną
   * @param new_name Nowa nazwa pliku z nagraniem
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   */
  void rename(const QString new_name);
  /**
   * @brief exists Zwraca informację, czy plik na który wskazuje klasa istnieje
   * @return True jeżeli istnieje, false w przeciwnym razie
   */
  bool exists()const;

  /**
   * @brief getConverter Zwraca klasę pozwalającą konwertować dane nagranie.
   * Jeżeli plik nie może być skonwertowany(np. nie obsługujemy danego formatu lub nie jest to plik muzyczny)
   * to zwracany jest nullptr
   * @return Klasa, pozwalająca skonwertować dane nagranie.
   * Jeśli nie ma klasy, która umie konwertować dany plik, zwraca nullptra
  */
  std::unique_ptr<MfccConverter> getConverter()const;

protected:

  /**
   * @brief checkFileExistance Sprawdza, czy plik opisany polem "record_path_" istnieje
   * Odświeża również pole "record_path_"
   * @throw FileNotFound Jeśli plik nie istnieje w filesystemie
   */
  void checkFileExistance()const;
  /**
   * @brief checkDirExistance Sprawdza, czy istnieje w filesystemie wskazany folder
   * @param dir Weryfikowany folder
   * @throw DirNotFound Jesli folder nie istnieje
   */
  void checkDirExistance(const QDir &dir)const;

  mutable QFileInfo record_path_;

};

#endif // RECORD_HPP
