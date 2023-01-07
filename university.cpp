/*
 * Yliopisto projekti
 * Nimi: Seyda Baysal
 * Opiskelija Numero: 291611
 * Sähköposti: seyda.baysal@tuni.fi
 * */

#include "university.hh"
#include "memory"

University::University():running_number_(111111)
{
}


University::~University()
{
    for ( auto course : courses_ ){
        delete course.second;
    }

    for ( auto account : accounts_ ){
        delete account.second;
    }

}


void University::add_course(Params params)
{
    if ( courses_.find(params.at(0)) != courses_.end() ){
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    } else {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(params.at(0), params.at(1));
    courses_.insert({n_course->get_code(), n_course});
}


void University::print_courses(Params)
{
    for ( auto course : courses_ ){
        course.second->print_info(true);
    }
}


void University::print_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_long_info();
}


void University::add_account(Params params)
{
    for( std::map<int, Account*>::iterator iter = accounts_.begin(); iter != accounts_.end(); ++iter ) {
        if( iter->second->get_email() == params.at(1) ) {
            std::cout << ALREADY_EXISTS << std::endl;
            return;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(params.at(0), params.at(1), account_number);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}


void University::print_accounts(Params)
{
    for ( auto account : accounts_ ){
        account.second->print();
    }
}


void University::print_account_info(Params params)
{
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(0)));
    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    iter->second->print();
}


void University::add_staff_to_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(1))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    courses_.at(params.at(0))->add_staff(accounts_.at(std::stoi(params.at(1))));
}


// Ensin loin n_instance olion.
// Etsin find metodin avulla sen kurssi pointterin.
// Lopuksi käytin new_instance() metodia.
// Lisäksi kaikki virhetilanteet.
void University::add_instance(Params params)
{
    if(courses_.find(params.at(0))==courses_.end()){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
     }

    Course* course = courses_.find(params.at(0))->second;
    if(course->has_instance(params.at(1))){
        std::cout <<INSTANCE_EXISTS<<std::endl;
        return;
    }

    Instance* newinstance = new Instance(params.at(1),utils::today, course);
    course->new_instance(newinstance);

}


// Ensin löydetään find metodin avulla course oliota
// -> toteutuskerran olio
// -> account oliota
// New_signups metodi ottaa account parametrin
// ja tallentaa sen signups_ vektoriin.
// Tarkasteltu myös metodiin liittyvät
// virhetilanteet
void University::sign_up_on_course(Params params)
{
    if(courses_.find(params.at(0))==courses_.end()){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
     }

    Course* course = courses_.find(params.at(0))->second;
    if(not course->has_instance(params.at(1))){
        std::cout <<CANT_FIND<<params.at(1)<<std::endl;
        return;
    }
    if(accounts_.find(std::stoi(params.at(2)))==accounts_.end()){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return;
     }  
    Instance* instance =
       course->get_instance(params.at(1));
     Account* account = accounts_.find(std::stoi(params.at(2)))->second;

     if (instance->new_signups(account, utils::today)){
        account->add_new_instance(instance);
        return;
     }

}


// Metodin avulla voidaan lisää suoritus
// kurssin toteutuskerrasta.
// Käytetään hyödyksi muissa luokissa toteutettuja
// metodeja.
// Virhe tarkastelut huomioon ottaen.
void University::complete_course(Params params)
{
    if(courses_.find(params.at(0))==courses_.end()){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
     }

        Course* course = courses_.find(params.at(0))->second;
        if(not course->has_instance(params.at(1))){
            std::cout <<CANT_FIND<<params.at(1)<<std::endl;
            return;
        }
        if(accounts_.find(std::stoi(params.at(2)))==accounts_.end()){
            std::cout << CANT_FIND << params.at(2) << std::endl;
            return;
         }

    Instance* instance =
       course->get_instance(params.at(1));
     Account* account = accounts_.find(std::stoi(params.at(2)))->second;

     account->course_completed(course, instance);
}


// Metodi tulostaa annetulle kursille ilmoittautuneet
// opiskelijat.
void University::print_signups(Params params)
{     
    if(courses_.find(params.at(0))==courses_.end()){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
     }

    auto course = courses_.find(params.at(0));
    course->second->print_signups();

}


// Metodi tulostaa annetun opiskelijan
// opiskelutilanteen.
void University::print_study_state(Params params)
{
    if(accounts_.find(std::stoi(params.at(0)))==accounts_.end()){
                std::cout << CANT_FIND << params.at(0) << std::endl;
                return;
             }

    auto account = accounts_.find(std::stoi(params.at(0)))->second;
    account->print_completed_and_current(true,true);
}


// Metodi tulostaa annetun opiskelijan
// kurssisuoritukset ja kok. opintopistemäärän.
void University::print_completed(Params params)
{
    if(accounts_.find(std::stoi(params.at(0)))==accounts_.end()){
                std::cout << CANT_FIND << params.at(0) << std::endl;
                return;
             }

    auto account = accounts_.find(std::stoi(params.at(0)))->second;
    account->print_completed_and_current(false,true);
}


void University::set_date(Params params)
{
    utils::today = Date(std::stoi(params.at(0)), std::stoi(params.at(1)), std::stoi(params.at(2)));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}


void University::advance_date(Params params)
{
    utils::today.advance_by(std::stoi(params.at(0)));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}


void University::advance_by_period(Params)
{
    utils::today.advance_by_period_length();
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
