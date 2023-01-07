/*
 * Yliopisto projekti
 * Nimi: Seyda Baysal
 * Opiskelija Numero: 291611
 * Sähköposti: seyda.baysal@tuni.fi
 * */

#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    void add_new_instance(Instance* instance);
    void course_completed(Course* completed_course, Instance* completed_instance);
    void print_completed_and_current(bool print_current, bool print_completed);
private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
    int credits_ = 0;
};

#endif // ACCOUNT_HH
