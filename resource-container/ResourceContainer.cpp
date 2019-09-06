#include "ResourceContainer.hpp"

QString ResourceContainer::getFalseImagePath()
{
  return QLibraryInfo::location(QLibraryInfo::PrefixPath) + "/images/false.png";


}

QString ResourceContainer::getTrueImagePath()
{
  return QLibraryInfo::location(QLibraryInfo::PrefixPath) + "/images/true.png";
}

QString ResourceContainer::getSfbcepPath()
{
  return QLibraryInfo::location(QLibraryInfo::PrefixPath) + "/bin/sfbcep";
}
