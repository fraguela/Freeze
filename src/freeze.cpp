#include <cstring>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <map>
#include <set>
#include "freeze/freeze.h"

namespace  {

struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

typedef std::set<const char*, ltstr> UsedFilesContainer_t;
UsedFilesContainer_t UsedFiles;

char *humbleBasename(const char * const file, const size_t len)
{ const char *p;

  //search file extension
  for (p = file + len - 1; (p > file) && (*p != '.'); p--);

  const char * const end_plus_1 = (p == file) ? (file + len) : p;
  
  for (p = end_plus_1 - 1; (p > file) && ((*p == '_') || !ispunct(*p)); p--);
  
  const char * const begin = ispunct(*p) ? (p + 1) : file;
  
  return strndup(begin, end_plus_1 - begin);
}
  
struct VarId {

  const char * const file_;
  const char * const var_name_;
  const char * const var_type_;
  const unsigned int line_;
  std::string        value_;

  VarId(const char * const file, const char * const var_name, const char * const var_type, const unsigned int line);

  //VarId(const VarId& other);

  void dump() const;
};

VarId::VarId(const char * const file, const char * const var_name, const char * const var_type, const unsigned int line) :
file_(file),
var_name_(var_name),
var_type_(var_type),
line_(line)
{ }

/*
VarId::VarId(const VarId& other) :
file_(other.file),
var_name_(other.var_name),
line_(other.line)
{ }
*/

// For debugging below
//#include<cstdio>
  
void VarId::dump() const
{ const char *p;
  int filled_filename;

  static const char const_qualifier_string[] =
#if __cplusplus < 201103L
  "const";
#else
  "constexpr";
#endif
  
  // Build file name ".name.freeze.h
  static const char Filename_suffix [] = ".freeze.h";
  const size_t len = strlen(file_);
  char * const filename = (char *)malloc(len + sizeof(Filename_suffix) + 2);
  char * const dirpos = strrchr(file_, '/');
  if (dirpos == NULL) { //only basename
    filename[0] = '.';
    for (int i = 0; i < len; i++) {
      filename[i + 1] = file_[i];
    }
    filled_filename = len;
  } else {
    for(p = file_; p != dirpos; p++)
      filename[p - file_] = *p;
    filename[p - file_] = *p; // copy last '/'
    p++;
    filename[p - file_] = '.';
    while (*p) {
      filename[p - file_ + 1] = *p;
      p++;
    }
    filled_filename = p - file_;
  }
  
  for (int i = 0; i < sizeof(Filename_suffix); i++) {
    filename[i + filled_filename + 1] = Filename_suffix[i];
  }

 //printf("%s Yields %s\n", file_, filename );
  
  const bool file_already_used = UsedFiles.count(filename);
  // Dump data
  std::ofstream f(filename, file_already_used ? std::ios_base::app : std::ios_base::out);
  if (!file_already_used) {
    char * const tmp = humbleBasename(file_, len);
    f << "#ifndef __FREEZE_" << tmp << std::endl;
    f << "#define __FREEZE_" << tmp << std::endl;
    free(tmp);
  }
  
  f << const_qualifier_string << ' ' << var_type_ << ' ' << var_name_ << '_' << line_ << " = " << value_ << ';' << std::endl;
  f.close();
  //std::cout << filename << " : " << file_ << ' ' << var_name_ << ' ' << line_ << '\n';
  
  if(file_already_used) {
    free(filename);
  } else {
    UsedFiles.insert(filename);
  }
}

typedef std::map<void *, VarId *> Freeze2VarIdMap_t;
Freeze2VarIdMap_t * Freeze2VarIdMap = NULL;
  
}; //namespace



namespace Freeze {
  
void registerFreeze(void *ptr, const char * const file, const char * const var_name, const char * const var_type, const unsigned int line)
{
  if(Freeze2VarIdMap == NULL) {
    Freeze2VarIdMap = new Freeze2VarIdMap_t;
  } else {
    assert(!Freeze2VarIdMap->count(ptr));
  }
  VarId * const value = new VarId(file, var_name, var_type, line);
  (*Freeze2VarIdMap)[ptr] = value;
  //Freeze2VarIdMap.insert(std::pair<void * const, VarId *>(ptr, value));
}

void registerFreezeValue(void *ptr, const std::ostringstream& ost)
{
  assert(Freeze2VarIdMap != NULL);
  assert(Freeze2VarIdMap->count(ptr));
  VarId *p = (*Freeze2VarIdMap)[ptr];
  p->value_ = ost.str();
}

class StaticFreeze {
public:
  ~StaticFreeze();
};
  
StaticFreeze::~StaticFreeze()
{
  if (Freeze2VarIdMap != NULL) {
    const Freeze2VarIdMap_t::iterator it_end = Freeze2VarIdMap->end();
    for (Freeze2VarIdMap_t::iterator it = Freeze2VarIdMap->begin(); it != it_end; ++it) {
      (*it).second->dump();
    }
    std::ofstream mainf(".freezes.h");
    mainf << "#ifndef __MAIN_FREEZE__" << std::endl;
    mainf << "#define __MAIN_FREEZE__" << std::endl;
    const UsedFilesContainer_t::iterator it_end2 = UsedFiles.end();
    for (UsedFilesContainer_t::iterator it = UsedFiles.begin(); it != it_end2; ++it) {
      std::ofstream f(*it, std::ios_base::app );
      f << "#endif" << std::endl;
      f.close();
      mainf << "#include \"" << *it << '\"' << std::endl;
    }
    mainf << "#endif" << std::endl;
    mainf.close();
  }
}

StaticFreeze TheStaticFreeze;

};
