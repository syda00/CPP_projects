/*
 * Yliopisto projekti
 * Nimi: Seyda Baysal
 * Opiskelija Numero: 291611
 * Sähköposti: seyda.baysal@tuni.fi
 * */

#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}


std::string Account::get_email()
{
    return email_;
}


// Tämä metodi lisää current_ vektoriin
// uuden toteutuskerran
void Account::add_new_instance(Instance* instance){
    current_.push_back(instance);
    std::cout<< SIGNED_UP << std::endl;

}


// Tämän metodin avulla toteutan university.cpp tiedostossa
// olevaa complete_course metodin.
void Account::course_completed(Course* completed_course,
                               Instance* completed_instance)
{
    if(std::find(current_.begin (), current_.end(),
                 completed_instance) == current_.end()){
        std::cout <<NO_SIGNUPS<<std::endl;
        return;
    }
    for(std::vector<Instance*>::size_type
        i = 0; i < current_.size(); i++){
        if (current_.at(i) == completed_instance){
            current_.erase(current_.begin() + i);
        }
    }
    completed_.push_back(completed_course);
    credits_ = credits_ + completed_course->get_credits();
    std::cout << COMPLETED << std::endl;
}


// Tämä metodi toeutetaan print_study_state &
// print_completed komentojen toteuttamiseen.
void Account::print_completed_and_current(bool print_current, bool print_completed){
    if (print_current){
        std::cout <<"Current: " <<std::endl;
        for (auto current: current_){
        current->print_course_information();
        }
    }
    if (print_completed){
        if (print_current and print_completed)
        {
            std::cout<<"Completed: "<<std::endl;
        }

        for (auto completed: completed_){
            completed->print_info(true);
        }
        std::cout<<"Total credits: "<<credits_<<std::endl;
    }
}
