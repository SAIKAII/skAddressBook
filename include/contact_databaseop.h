#ifndef ADDRESSBOOK_INCLUDE_DATABASEOP_H_
#define ADDRESSBOOK_INCLUDE_DATABASEOP_H_

#include "contact.h"
#include <mysql/mysql.h>
#include <string>
#include <vector>
#include <memory>

class ContactDatabaseOP{
public:
  static ContactDatabaseOP *get_instance();
  std::shared_ptr<std::vector<Contact>> query_contacts(const std::string &);
  bool update_tbl_contact(const std::string &);
  ~ContactDatabaseOP();

private:
  ContactDatabaseOP();
  ContactDatabaseOP(const ContactDatabaseOP&) = delete;

  MYSQL *conn_;
};

#endif
