/*
 * Tässä tiedostossa olen toteuttanut seuraavia metodeja ja
 * käyttänyt sitä tarvittavissa paikoissa.
 * Yliopisto projekti
 * Nimi: Seyda Baysal
 * Opiskelija Numero: 291611
 * Sähköposti: seyda.baysal@tuni.fi
 * */

#include "instance.hh"
#include "course.hh"

using namespace std;


// Rakentaja metodi
Instance::Instance(string name, Date starting_date, Course* course_that_belongs_to):
name_(name),starting_date(starting_date), course_(course_that_belongs_to)
{

}


// Purkaaja
Instance::~Instance()
{

}


void Instance::print(){
        cout << name_ <<endl;
        cout << "    Starting date: ";
        starting_date.print();
        cout<<endl;
        cout << "    Amount of students: "<< amount_ <<endl;
}


// Tässä metodissa käyn for rakenteen
// avulla tiliä. Jotka on tallennettu
// signups_ vektoriin.
// Kutsutaan sitten jokaiselle tilille
// print metodia.
void Instance::print_students(){

    for(auto value : signups_){
        cout<<"    ";
        value->print();
    }
}


// Tässä toteutan apu metodin, johon tallennan
// account olio vektoriin nimeltään signups.
bool Instance::new_signups(Account *n_signups, Date date){

    // Tarkistan ettei siitä vektorista
    // löytysisi sama asia monta kertaa.
    if(find(signups_.begin(),
            signups_.end(),n_signups)
            != signups_.end()){
        cout<<ALREADY_REGISTERED<<endl;
        return false;
    }
    if(starting_date.operator<(date)){
        cout<< LATE <<endl;
        return false;
    }
    signups_.push_back(n_signups);
    // Sen jälkeen kun osallistuja
    // on tallennettu sitä kasvatetaan yhdellä
    ++amount_;
    return true;
}


// Tässä metodissa tarkistan ensin onko annettu
// parametri sama kuin toteutuskerran nimi.
bool Instance::is_named(string param){
    if(name_ == param){
        return true;
    }
    return false;
}


// Tämä metodi on toteutettu apu metodina
void Instance::print_course_information(){
    course_->print_info(false);
    cout <<" "<<name_<<endl;
}
