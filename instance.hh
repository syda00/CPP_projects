/*
 * Yliopisto projekti
 * Nimi: Seyda Baysal
 * Opiskelija Numero: 291611
 * Sähköposti: seyda.baysal@tuni.fi
 * */

#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    Instance(std::string name, Date starting_date, Course* course_that_belongs_to);
    ~Instance();

    void print();
    void print_students();
    bool new_signups(Account *n_signus, Date date);
    bool is_named(std::string param);
    void print_course_information();
	
private:
    std::string name_;
    int amount_ = 0;
    Date starting_date;
    Course* course_;
    //Luodaan vektori nimeltään signups_ johon tallennetetaan
    //tilin pointtereitä
    std::vector<Account*> signups_;


};

#endif // INSTANCE_HH
