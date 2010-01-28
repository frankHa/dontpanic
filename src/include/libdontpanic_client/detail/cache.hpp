#ifndef DP_CLIENT_DETAIL_CACHE_HPP
#define DP_CLIENT_DETAIL_CACHE_HPP

namespace dp
{
  namespace client
  {
    namespace detail
    {
      template<typename ObjT, typename NullT>
      class cache
      {
        public:
          typedef ObjT object;
          typedef NullT null_t;
          typedef QList<object> objectlist;
          
        public:
          cache()
          :_M_initialized(false){}
          
          
        public:   
          template<typename remote_ptr>
          object at(int index, remote_ptr remote)
          {
            assure_we_are_initialized(remote);
            return _M_objects.at(index);
          }
          
          template<typename id_t, typename remote_ptr>
          object load(id_t const& id, remote_ptr remote)
          {
            assure_we_are_initialized(remote);
            object ref(id);
            int index = _M_objects.indexOf(ref);
            if(index == -1)
            {
              return null_t();
            }
            return _M_objects.value(index);
          }
          
          void store(object const& o)
          {
            int index = _M_objects.indexOf(o);
            if(index==-1)
            {
              _M_objects.append(o);
            }
            else
            {
              _M_objects.replace(index, o);
            }
          }
          
          template<typename remote_ptr>
          objectlist find_all(remote_ptr remote)
          {
            assure_we_are_initialized(remote);
            return _M_objects;
          }
          
          void remove_all(object const& o)
          {
            _M_objects.removeAll(o);
          }
          
        private:
          template<typename remote_ptr>
          void assure_we_are_initialized(remote_ptr remote)
          {
            if(_M_initialized) return;
            _M_objects = remote->findAll();
            _M_initialized = true;
          }
          
        private:
          bool _M_initialized;
          objectlist _M_objects;          
      };
    }//detail
  }//client
}//dp

#endif //DP_CLIENT_DETAIL_CACHE_HPP
