#ifndef DP_REPORTS_CATEGORY_H
#define DP_REPORTS_CATEGORY_H
// ---------------------------------------------------------------------------------
#include <libdontpanic/defines.hpp>
#include <libdontpanic/uuid.h>
#include <libdontpanic/action.hpp>
// ---------------------------------------------------------------------------------
namespace dp
{
  // ---------------------------------------------------------------------------------
  namespace reports
  {
    namespace grouping
    {
      // ---------------------------------------------------------------------------------
      class category
      {
        public:
          category();
          category ( category *embed );
          virtual ~category();
        public:
          // ---------------------------------------------------------------------------------
          virtual bool matches ( Action const& a ) const = 0;
          // ---------------------------------------------------------------------------------
          virtual void embed ( category *cat );
          // ---------------------------------------------------------------------------------
        protected:
          category *embedded;
      };
      // ---------------------------------------------------------------------------------
      class null: public category
      {
        public:
          null() : category ( 0 ) {}
        public:
          bool matches ( Action const& a ) const
          {
            if(embedded == 0)return true;
            return embedded->matches(a);
          }          
      };
      // ---------------------------------------------------------------------------------
      class no: public category
      {
        public:
          no() : category ( 0 ) {}
        public:
          bool matches ( Action const& a ) const
          {
            return false;
          }
      };
      // ---------------------------------------------------------------------------------
      class task
            : public category
      {
          // ---------------------------------------------------------------------------------
        public:
          task ( Uuid const& t )
              : _M_task ( t ) {}
          // ---------------------------------------------------------------------------------
          bool matches ( Action const&a ) const
          {
            if ( a.task() != _M_task ) {return false;}
            return embedded->matches ( a );
          }
          // ---------------------------------------------------------------------------------
        private:
          Uuid _M_task;
      };
      // ---------------------------------------------------------------------------------
      class project
            : public category
      {
          // ---------------------------------------------------------------------------------
        public:
          project ( Uuid const& p )
              : _M_project ( p ) {}
          // ---------------------------------------------------------------------------------
          bool matches ( Action const&a ) const
          {
            if ( a.project() != _M_project ) {return false;}
            return embedded->matches ( a );
          }
          // ---------------------------------------------------------------------------------
        private:
          Uuid _M_project;
          // ---------------------------------------------------------------------------------
      };
      // ---------------------------------------------------------------------------------
    }
  }
  // ---------------------------------------------------------------------------------
}
// ---------------------------------------------------------------------------------
#endif //DP_REPORTS_CATEGORY_H
