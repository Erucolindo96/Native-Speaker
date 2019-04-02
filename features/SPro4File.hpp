#ifndef SPRO4FILE_HPP
#define SPRO4FILE_HPP

#include"record-base/Record.hpp"

class SPro4File: public Record
{
public:
  SPro4File()=default;
  SPro4File(const SPro4File &other)=default;
  SPro4File& operator=(const SPro4File &other)=default;
  SPro4File(SPro4File &&other)=default;
  SPro4File& operator=(SPro4File &&other)=default;

  /**
   * @brief setPath Ustawia ścieżkę do pliku z nagraniem, wskazywanego przez klasę
   * @param rec_path Scieżka do nagrania
   * @throw FileNotFound jeśli nie można znaleźć pliku określonego daną ścieżką
   */
  void setPath(const QString &rec_path) override;
  /**
   * @brief setPath Ustawia ścieżkę do pliku z nagraniem, wskazywanego przez klasę
   * @param rec_name pełna nazwa pliku
   * @param rec_dir folder, w którym znajduje się nagranie
   * @throw FileNotFound jeśli w danym folderze nie ma nagrania o danej nazwie
   * @throw DirNotFound jeśli wskazany jako parametr folder nie istnieje
   */
  void setPath(const QString &rec_name, const QDir &rec_dir) override;

  /**
   * @brief getRecordInfo Zwraca informację o nagraniu wskazywanym przez klasę
   * @return Informację o nagraniu wskazywanym przez klasę
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   */
  QFileInfo getRecordInfo()const override;

  /**
   * @brief copy Kopiuje nagranie wskazywane przez klasę do folderu podanego jako parametr
   * @param dest_dir Folder, do którego zostanie skopiowane nagranie
   * @return Odnośnik do kopii nagrania
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   * @throw DirNotFound jeśli wskazany jako parametr folder nie istnieje
   */
  Record copy(const QDir &dest_dir)const override;
  /**
   * @brief move Przemieszcza nagranie wskazywane przez klasę do innego folderu
   * @param dest_dir Folder, do którego zostanie przeniesione nagranie
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   * @throw DirNotFound jeśli wskazany jako parametr folder nie istnieje
   */
  void move(const QDir &dest_dir) override;

  /**
   * @brief rename Zmienia nazwę nagrania na inną
   * @param new_name Nowa nazwa pliku z nagraniem
   * @throw FileNotFound jeśli plik wskazywany przez klasę nie istnieje
   */
  void rename(const QString new_name) override;
  /**
   * @brief exists Zwraca informację, czy plik na który wskazuje klasa istnieje
   * @return True jeżeli istnieje, false w przeciwnym razie
   */
  bool exists()const override;

  std::unique_ptr<MfccConverter> getConverter()const = delete;

protected:
  void validate()const;

};

#endif // SPRO4FILE_HPP
