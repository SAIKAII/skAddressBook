#ifndef ADDRESSBOOK_INCLUDE_ADDRESSBOOK_H_
#define ADDRESSBOOK_INCLUDE_ADDRESSBOOK_H_

#include "contact.h"
#include <vector>
#include <memory>

class AddressBook{
public:
  AddressBook();
  void print_info();
  bool insert_contact(const Contact * const contact);
  bool delete_contact(int index);
  void search_by_name(const std::string &name);
  void search_by_ip(const std::string &ip);
  void search_all();

private:
  void all_contacts();

  std::shared_ptr<std::vector<Contact>> contacts_v_;
};

#endif
