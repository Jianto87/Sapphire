#ifndef SAPPHIRE_CONNECTION_H
#define SAPPHIRE_CONNECTION_H

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <map>
#include "MySqlBase.h"

typedef struct st_mysql MYSQL;

namespace Mysql
{
   using optionMap = std::map< mysqlOption, std::string >;
   class MySqlBase;
   class Statement;
   class PreparedStatement;

   class Connection : public boost::enable_shared_from_this< Connection >
   {
   public:
      Connection( boost::shared_ptr< MySqlBase > pBase,
                  const std::string& hostName,
                  const std::string& userName,
                  const std::string& password,
                  uint16_t port = 3306);

      Connection( boost::shared_ptr< MySqlBase > pBase,
                  const std::string& hostName,
                  const std::string& userName,
                  const std::string& password,
                  const optionMap& options,
                  uint16_t port = 3306 );

      virtual ~Connection();

      void close();
      bool isClosed() const;

      bool ping();
      
      void setOption( enum mysqlOption option, const void* arg );
      void setOption( enum mysqlOption option, uint32_t arg );
      void setOption( enum mysqlOption option, const std::string& arg );

      boost::shared_ptr< MySqlBase > getMySqlBase() const;

      void setAutoCommit( bool autoCommit );
      bool getAutoCommit();

      std::string escapeString( const std::string& inData );

      void setSchema( const std::string& catalog );

      boost::shared_ptr< Statement > createStatement();

      void beginTransaction();
      void commitTransaction();
      void rollbackTransaction();

      std::string getSchema();

      std::string getError();
      uint32_t getErrorNo();

      bool isReadOnly();
      void setReadOnly( bool readOnly );

      bool isValid();

      bool reconnect();

      boost::shared_ptr< Mysql::PreparedStatement > prepareStatement( const std::string& sql );
      
      std::string getLastStatementInfo();

      MYSQL* getRawCon();

   private:
      boost::shared_ptr< MySqlBase > m_pBase;
      MYSQL* m_pRawCon;
      bool m_bConnected;

      Connection( const Connection& );
      void operator=( Connection& );
   };


}

#endif //SAPPHIRE_CONNECTION_H