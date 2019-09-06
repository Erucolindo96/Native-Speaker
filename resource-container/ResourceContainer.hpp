#ifndef RESOURCECONTAINER_HPP
#define RESOURCECONTAINER_HPP

#include<QString>
#include<QLibraryInfo>
class ResourceContainer
{
public:

  static QString getFalseImagePath();
  static QString getTrueImagePath();

  static QString getSfbcepPath();
};

#endif // RESOURCECONTAINER_HPP
