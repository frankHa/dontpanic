#ifndef DP_ENUM_H
#define DP_ENUM_H

#include <QString>
#include <QStringList>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  /**
   * \brief common base template for defining rich enum types.
   * \example
   * \code
     class SomeEnum
     :public cf::Enum&lt;SomeEnum&gt;
     {
      typedef cf::Enum&lt;SomeEnum&gt base;
      public:
        enum value{VALUE1, VALUE2, INVALID=-1};
      public:
      SomeEnum(value v):base(v){}

      //returns the string representations of the enum values.
      //it is important to match the order of native enum declarations
      static QStringList values()
      {
        return QStringList()<<"VALUE1"<<"VALUE2";
      }

      //returns the pretty string representations of the enum values
      //meant for being used in a user display.
      //it is important to match the order of native enum declarations.
      //note, that this method is optional.
      static QStringList values()
      {
        return QStringList()<<"Value 1"<<"Value 2";
      }
     };
   * \endcode
   */
  template<typename EnumType>
  class Enum
  {
      // ---------------------------------------------------------------------------------
      typedef EnumType enum_type;
      // ---------------------------------------------------------------------------------
    public:
      // ---------------------------------------------------------------------------------
      Enum ( int v ) : _M_value ( v ) {}
      int ordinal_number() const
      {
        return _M_value;
      }
      // ---------------------------------------------------------------------------------
      static QStringList pretty_names()
      {
        return enum_type::values();
      }
      // ---------------------------------------------------------------------------------
      static enum_type value_of ( int iVal )
      {
        return enum_type ( static_cast<typename enum_type::value> ( iVal ) );
      }
      // ---------------------------------------------------------------------------------
      static enum_type value_of ( QString name )
      {
        QString lower_name = name.toLower();
        QStringList _values = enum_type::values();
        for(int i=0; i<_values.size();++i )
        {
          if(QString::compare(_values[i].toLower(), lower_name)==0 )
          {
            return value_of(i);
          }
        }
        return value_of(enum_type::INVALID);
      }
      // ---------------------------------------------------------------------------------
      QString to_string() const
      {
        if(!is_valid())
        {
          return "INVALID";
        }
        return enum_type::values() [_M_value];
      }
      // ---------------------------------------------------------------------------------
      QString pretty_name() const
      {
        if(!is_valid())
        {
          return "INVALID";
        }
        return enum_type::pretty_names() [_M_value];
      }
      // ---------------------------------------------------------------------------------
      bool is_valid() const
      {
        return _M_value != enum_type::INVALID;
      }
      // ---------------------------------------------------------------------------------
      int value() const
      {
        return _M_value;
      }
      // ---------------------------------------------------------------------------------
    private:
      // ---------------------------------------------------------------------------------
      int _M_value;
      // ---------------------------------------------------------------------------------
  };
  // ---------------------------------------------------------------------------------
}//cf
template<typename EnumType>
bool operator == ( EnumType const& l, EnumType const& r )
{
  if ( !l.is_valid() || !r.is_valid() )
  {
    return false;
  }
  return l.ordinal_number() == r.ordinal_number();
}
// ---------------------------------------------------------------------------------
template<typename EnumType>
bool operator == ( EnumType const& l, typename EnumType::value r )
{
  if ( !l.is_valid() )
    return false;
  return l.ordinal_number() == r;
}

template<typename EnumType>
bool operator == ( typename EnumType::value l, EnumType const& r )
{
  if ( !r.is_valid() )
    return false;
  return r.ordinal_number() == l;
}
// ---------------------------------------------------------------------------------
#endif //DP_ENUM_H
