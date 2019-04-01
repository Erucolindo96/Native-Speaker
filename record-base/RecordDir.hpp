#ifndef MODELDIR_HPP
#define MODELDIR_HPP
#include"record-base/Record.hpp"
#include<QDir>
#include<vector>

/**
 * @brief The RecordDir class Klasa reprezentująca folder w bazie próbek.
 * Odpowiada za dodawanie i usuwanie nagrań z folderu, który reprezentuje
 * Instancje klasy tworzy RecordDirManager.
 * @see RecordDirManager
 */
class RecordDir
{

public:

  RecordDir(const RecordDir &other) = default;
  RecordDir& operator=(const RecordDir &other) = default;
  RecordDir(RecordDir &&other) = default;
  RecordDir& operator=(RecordDir &&other) = default;

  /**
   * @brief addRecord Dodaje nagranie do folderu
   * @param rec dodawane nagranie
   * @throw FileNotFound jeśli rec nie reprezentuje żadnego pliku w Filesystemie
   * @throw DirNotFound jeśli folder, którego reprezentuje klasa nie istnieje
   */
  void addRecord(const Record &rec);
  /**
   * @brief list Listuje folder reprezentowany przez klasę i zwraca wektor plików zawartych w katalogu
   * @return Wektor plików, które zawiera katalog
   * @throw DirNotFound jeśli folder, którego reprezentuje klasa nie istnieje
   */
  const std::vector<Record> list()const;
  /**
   * @brief removeAll Usuwa wszystkie nagrania z folderu
   * @throw DirNotFound jeśli folder, którego reprezentuje klasa nie istnieje
   */
  void removeAll();
  /**
   * @brief haveRecord Zwraca inforację, czy dane nagranie znajduje się z folderze reprezentowanym przez klasę
   * @param other nagranie o które pytamy
   * @return True jeśli nagranie znajduje się w folderze, w przeciwnym razie false
   * @throw DirNotFound jeśli folder, którego reprezentuje klasa nie istnieje
   */
  bool haveRecord(const Record &other)const;
  /**
   * @brief exists Zwraca informację, czy folder którego reprezentuje klasa istnieje
   * @return True jeśli istnieje, false jesli nie istnieje
   */
  bool exists()const;

protected:

  mutable QDir dir_;
  RecordDir() = default;
  void checkExistanceOfDir()const;
  void setDir(const QDir &dir);
  QDir getDir()const;

  friend class RecordDirManager;
};

#endif // MODELDIR_HPP
