
#include "iostream"
#include "fstream"
#include "time.h"
#include "chrono"
#include "stdio.h"
#include "stdlib.h"

long locate;
int loc;
int posrec;

class RecCount {
    
public:
    
    int reccount;
}rec, trec;

class User {
    
    std::string username;
    std::string password;
    long accNum;
    std::string email;
    long contact;
    long double balance;
    
public:
    
    std::string getUsername() {
        
        std::cin>>this->username;
        
        return this->username;
    }
    
    std::string useUsername() {
        
        return this->username;
    }
    
    void tsetUserName(std::string user) {
        
        this->username = user;
    }
    
    void tsetPass(std::string pass) {
        
        this->password = pass;
    }
    
    void tsetAcc(long acc) {
        
        this->accNum = acc;
    }
    
    void tsetMail(std::string mail) {
        
        this->email = mail;
    }
    
    void tsetContact(long cont) {
        
        this->contact = cont;
    }
    
    void tsetBal(long double bal) {
        
        this->balance = bal;
    }
    
    void setBal() {
        
        this->balance = 0;
    }
    
    void setBalDeduct(long double amt) {
        
        this->balance -= amt;
    }
    
    void setBalDep(long double depamt) {
        
        this->balance += depamt;
    }
    
    void setNum() {
        
        srand(time(0));
        
        int num = (rand()%13001)+10000001;
        
        this->accNum = num;
    }
    
    std::string getPassword() {
        
        std::cin>>this->password;
        
        while(password.length()<9) {
            
            std::cout<<"Re-enter your password: ";
            std::cin>>this->password;
        }
        
        return this->password;
    }
    
    std::string usePassword() {
        
        return this->password;
    }

    std::string getMail() {
        
        std::cin>>this->email;
        
        return this->email;
    }
    
    long getContact() {
        
        std::cin>>this->contact;
        
        return this->contact;
    }
    
    long useAcc() {
        
        return this->accNum;
    }
    
    long useContact() {
        
        return this->contact;
    }
    
    std::string useMail() {
        
        return this->email;
    }
    
    long double useBal() {
        
        return this->balance;
    }

}user[100], usert[100];

void createAcc() {
    
    std::ifstream rin("RecCount", std::ios::in | std::ios::binary);
    std::ofstream rout("tRecCount", std::ios::out | std::ios::binary | std::ios::app);
    
    while(!rin.eof()) {
        
        rin.read((char*)&rec, sizeof(rec));
        posrec = rec.reccount;
        posrec +=1;
        
        trec.reccount = posrec;
        
        rout.write((char*)&trec, sizeof(trec));
        
        rout.close();
        rin.close();
        break;
    }
    
    remove("RecCount");
    rename("tRecCount", "RecCount");
    
    std::string tuser;
    std::string tpass;
    std::string mail;
    long cont;
    
    std::cout<<"Create your username: ";
    tuser = user[posrec].getUsername();
    std::cout<<"Enter a strong password(min- 9 characters),(Password cannot be changed later): ";
    tpass = user[posrec].getPassword();
    
    std::cout<<"Enter your email: ";
    mail = user[posrec].getMail();
    
    std::cout<<"Enter your contact: ";
    cont = user[posrec].getContact();
    
    user[posrec].setNum();
    user[posrec].setBal();
    
    std::ofstream userFile("User", std::ios::out | std::ios::binary | std::ios::app);
    
    userFile.write((char*)&user[posrec], sizeof(user[posrec]));
    userFile.close();
    
    std::cout<<"Your account has been created...\n\n";
    std::cout<<"Now you can perform all your banking tasks...\n";
    
    std::ofstream add("Notify", std::ios::out | std::ios::app);
    
    auto time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    add<<"New user joined the account server...\n";
    add<<"Time : "<<ctime(&time_now)<<"\n";
    add<<"Username : "<<tuser;
    
    add<<"\n\n";
    add.close();
}

void logAcc() {
    
inpUs:
    
    int i=0;
    
    std::ifstream rin("RecCount", std::ios::in | std::ios::binary);
    
    while(!rin.eof()) {
        
        rin.read((char*)&trec, sizeof(trec));
        posrec = trec.reccount;
        rin.close();
        break;
    }
    
    std::ifstream userCheck("User", std::ios::in | std::ios::binary);
    std::string tuser, tpass;
    
    std::cout<<"Enter your Username: ";
    std::cin>>tuser;
    
    userCheck.seekg(0);
    
    while(!userCheck.eof()) {
        
        userCheck.read((char*)&user[i], sizeof(user[i]));
        
        if(user[i].useUsername()==tuser) {
            
        rep:
            
            locate = userCheck.tellg();
            loc = i;
            std::cout<<"Enter your password: ";
            std::cin>>tpass;
            
            if(user[i].usePassword()==tpass) {
                
                std::cout<<"Log in succesful...\n";
                userCheck.close();
                goto end;
            } else {
                
                std::cout<<"Try again...\n";
                goto rep;
            }
        }
        i++;
        
        if(i>(posrec)) {
            
            break;
        }
    }

    userCheck.close();
    
    std::cout<<"User not found as such, try again...\n";
    goto inpUs;
    
end:
    std::cout<<"";
    
    std::ofstream add("Notify", std::ios::out | std::ios::app);
    
    auto time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    add<<"A user logged in the account server...\n";
    add<<"Time : "<<ctime(&time_now)<<"\n";
    add<<"Username : "<<tuser;
    
    add<<"\n\n";
    add.close();
}

void viewAcc() {
    
    std::cout<<"\n";
    std::ifstream userC("User", std::ios::in | std::ios::binary);
    
    userC.seekg((locate-1)*sizeof(user));
    
    while(!userC.eof()) {
        
        userC.read((char*)&user[loc], sizeof(user[loc]));
        
        std::cout<<"Name: "<<user[loc].useUsername()<<"\n";
        std::cout<<"Account Number: "<<user[loc].useAcc()<<"\n";
        std::cout<<"Email: "<<user[loc].useMail()<<"\n";
        std::cout<<"Contact: "<<user[loc].useContact()<<"\n";
        std::cout<<"Balance: "<<user[loc].useBal()<<"\n";
        break;
    }
    
    userC.close();
}

void editAcc() {
    
    std::cout<<"\n(Only contact or mail can be changed...)\n\n";
    
    int i=0;
    
    std::string name;
    std::string pass;
    long acc;
    std::string mail;
    long cont;
    long double bal;
    
    std::cout<<"\n";
    
    std::ifstream oldUser("User", std::ios::in | std::ios::binary);
    std::ofstream newUser("newUser", std::ios::out | std::ios::binary | std::ios::app);
    
    oldUser.seekg((locate-1)*sizeof(user));
    
    while(!oldUser.eof()) {
        
        oldUser.read((char*)&user[loc], sizeof(user[loc]));
        
        name = user[loc].useUsername();
        usert[loc].tsetUserName(name);
        
        pass = user[loc].usePassword();
        usert[loc].tsetPass(pass);
        
        acc = user[loc].useAcc();
        usert[loc].tsetAcc(acc);
        
        bal = user[loc].useBal();
        usert[loc].tsetBal(bal);
        
        break;
    }
    
    std::cout<<"Enter your new mailID : ";
    std::cin>>mail;
    usert[loc].tsetMail(mail);
    
    std::cout<<"Enter your new contact : ";
    std::cin>>cont;
    usert[loc].tsetContact(cont);
    
    newUser.write((char*)&usert[loc], sizeof(usert[loc]));
    newUser.close();
    oldUser.close();
    
    std::ifstream oldUser_("User", std::ios::in | std::ios::binary);
    std::ofstream newUser_("newUser", std::ios::out | std::ios::binary | std::ios::app);
    
    oldUser_.seekg(0);
    
    while(oldUser_.read((char*)&user[i], sizeof(user[i]))) {
        
        if(user[i].useUsername() != name) {
            
            newUser_.write((char*)&user[i], sizeof(user[i]));
        }
        
        i++;
        
        if(i>(posrec)) {
            
            break;
        }
    }
    
    oldUser_.close();
    newUser_.close();
    
    remove("User");
    rename("newUser", "User");
}

void withdrawAcc() {
    
    long double amt, pramt=0;
    
    int i=0;
    
    std::string name;
    std::string pass;
    long acc;
    std::string mail;
    long cont;
    long double bal;
    
    std::cout<<"\n";
    
    std::ifstream oldUser("User", std::ios::in | std::ios::binary);
    std::ofstream newUser("newUser", std::ios::out | std::ios::binary | std::ios::app);
    
    oldUser.seekg((locate-1)*sizeof(user));
    
    while(!oldUser.eof()) {
        
        oldUser.read((char*)&user[loc], sizeof(user[loc]));
        
        name = user[loc].useUsername();
        usert[loc].tsetUserName(name);
        
        pass = user[loc].usePassword();
        usert[loc].tsetPass(pass);
        
        acc = user[loc].useAcc();
        usert[loc].tsetAcc(acc);
        
        mail = user[loc].useMail();
        usert[loc].tsetMail(mail);
        
        cont = user[loc].useContact();
        usert[loc].tsetContact(cont);
        
        std::cout<<"Enter amount to be withdrawed : ";
        std::cin>>amt;
        pramt = amt;
        
        bal = user[loc].useBal();
        
        if(user[loc].useBal()<amt) {
            
            std::cout<<"\nLow Balance(Cannot withdraw)...\n";
            goto readc;
        } else {
            
            bal-=amt;
            usert[loc].tsetBal(bal);
        }
        
readc:
    
        break;
    }
    
    newUser.write((char*)&usert[loc], sizeof(usert[loc]));
    newUser.close();
    oldUser.close();
    
    std::ifstream oldUser_("User", std::ios::in | std::ios::binary);
    std::ofstream newUser_("newUser", std::ios::out | std::ios::binary | std::ios::app);
    
    oldUser_.seekg(0);
    
    while(oldUser_.read((char*)&user[i], sizeof(user[i]))) {
        
        if(user[i].useUsername() != name) {
            
            newUser_.write((char*)&user[i], sizeof(user[i]));
        }
        
        i++;
        
        if(i>(posrec)) {
            
            break;
        }
    }
    
    oldUser_.close();
    newUser_.close();
    
    remove("User");
    rename("newUser", "User");
    
    std::ofstream add("Transact", std::ios::out | std::ios::app);
    
    auto time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    add<<"A user withdrawed some amount from his account...\n";
    add<<"Time : "<<ctime(&time_now)<<"\n";
    add<<"Username : "<<name<<"\n";
    add<<"Amount : "<<pramt;
    
    add<<"\n\n";
    add.close();
}

void depositAcc() {
    
    long double amt, pramt=0;
        
        int i=0;
        
        std::string name;
        std::string pass;
        long acc;
        std::string mail;
        long cont;
        long double bal;
        
        std::cout<<"\n";
        
        std::ifstream oldUser("User", std::ios::in | std::ios::binary);
        std::ofstream newUser("newUser", std::ios::out | std::ios::binary | std::ios::app);
        
        oldUser.seekg((locate-1)*sizeof(user));
        
        while(!oldUser.eof()) {
            
            oldUser.read((char*)&user[loc], sizeof(user[loc]));
            
            name = user[loc].useUsername();
            usert[loc].tsetUserName(name);
            
            pass = user[loc].usePassword();
            usert[loc].tsetPass(pass);
            
            acc = user[loc].useAcc();
            usert[loc].tsetAcc(acc);
            
            mail = user[loc].useMail();
            usert[loc].tsetMail(mail);
            
            cont = user[loc].useContact();
            usert[loc].tsetContact(cont);
            
            std::cout<<"Enter amount to be deposited : ";
            std::cin>>amt;
            pramt = amt;
            
            bal = user[loc].useBal();
            
            bal+=amt;
            usert[loc].tsetBal(bal);
            
            break;
        }
        
        newUser.write((char*)&usert[loc], sizeof(usert[loc]));
        newUser.close();
        oldUser.close();
        
        std::ifstream oldUser_("User", std::ios::in | std::ios::binary);
        std::ofstream newUser_("newUser", std::ios::out | std::ios::binary | std::ios::app);
        
        oldUser_.seekg(0);
        
        while(oldUser_.read((char*)&user[i], sizeof(user[i]))) {
            
            if(user[i].useUsername() != name) {
                
                newUser_.write((char*)&user[i], sizeof(user[i]));
            }
            
            i++;
            
            if(i>(posrec)) {
                
                break;
            }
        }
        
        oldUser_.close();
        newUser_.close();
        
        remove("User");
        rename("newUser", "User");
    
        std::ofstream add("Transact", std::ios::out | std::ios::app);
        
        auto time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        
        add<<"A user deposited some amount to his account...\n";
        add<<"Time : "<<ctime(&time_now)<<"\n";
        add<<"Username : "<<name<<"\n";
        add<<"Amount : "<<pramt;
        
        add<<"\n\n";
        add.close();
}

void depTransAcc(long double trans) {
    
    std::string name_;
    
    std::ifstream rin("RecCount", std::ios::in | std::ios::binary);
        
        while(!rin.eof()) {
            
            rin.read((char*)&trec, sizeof(trec));
            posrec = trec.reccount;
            rin.close();
            break;
        }

    recheck:
        
        int j=0;
        
        long fetch;
        bool che=false;
        
        std::cout<<"\n";
        
        std::cout<<"Enter the account number for transfer : ";
        std::cin>>fetch;
        
        std::ifstream userC("User", std::ios::in | std::ios::binary);
        
        userC.seekg(0);
        
        while(!userC.eof()) {
            
            userC.read((char*)&user[j], sizeof(user[j]));
            
            if(user[j].useAcc() == fetch) {
                
                locate = userC.tellg();
                loc = j;
                che = true;
                name_ = user[j].useUsername();
                
                break;
            }
            j++;
            
            if(j>(posrec)) {
                
                break;
            }
        }
        
        userC.close();
        
        if(che == false) {
            
            std::cout<<"Not found, try again...\n";
            goto recheck;
        }
    
    long double amt;
    
    int i=0;
    
    std::string name;
    std::string pass;
    long acc;
    std::string mail;
    long cont;
    long double bal;
    
    std::cout<<"\n";
    
    
    
    std::ifstream oldUser("User", std::ios::in | std::ios::binary);
    std::ofstream newUser("newUser", std::ios::out | std::ios::binary | std::ios::app);
    
    oldUser.seekg((locate-1)*sizeof(user));
    
    while(!oldUser.eof()) {
        
        oldUser.read((char*)&user[loc], sizeof(user[loc]));
        
        name = user[loc].useUsername();
        usert[loc].tsetUserName(name);
        
        pass = user[loc].usePassword();
        usert[loc].tsetPass(pass);
        
        acc = user[loc].useAcc();
        usert[loc].tsetAcc(acc);
        
        mail = user[loc].useMail();
        usert[loc].tsetMail(mail);
        
        cont = user[loc].useContact();
        usert[loc].tsetContact(cont);
        
        amt = trans;
        
        bal = user[loc].useBal();
        
        bal+=amt;
        usert[loc].tsetBal(bal);
        
        break;
    }
    
    newUser.write((char*)&usert[loc], sizeof(usert[loc]));
    newUser.close();
    oldUser.close();
    
    std::ifstream oldUser_("User", std::ios::in | std::ios::binary);
    std::ofstream newUser_("newUser", std::ios::out | std::ios::binary | std::ios::app);
    
    oldUser_.seekg(0);
    
    while(oldUser_.read((char*)&user[i], sizeof(user[i]))) {
        
        if(user[i].useUsername() != name) {
            
            newUser_.write((char*)&user[i], sizeof(user[i]));
        }
        
        i++;
        
        if(i>(posrec)) {
            
            break;
        }
    }
    
    oldUser_.close();
    newUser_.close();
    
    remove("User");
    rename("newUser", "User");
    
    std::ofstream add("Transact", std::ios::out | std::ios::app);
    
    auto time_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    
    add<<"Receiver's Details :\n";
    add<<"Time : "<<ctime(&time_now)<<"\n";
    add<<"Username : "<<name_<<"\n";
    
    add.close();
}

void transferAcc() {
    
    long double amt;
        
        int i=0;
    
        long double transamt=0;
        
        std::string name;
        std::string pass;
        long acc;
        std::string mail;
        long cont;
        long double bal;
        
        std::cout<<"\n";
        
        std::ifstream oldUser("User", std::ios::in | std::ios::binary);
        std::ofstream newUser("newUser", std::ios::out | std::ios::binary | std::ios::app);
        
        oldUser.seekg((locate-1)*sizeof(user));
        
        while(!oldUser.eof()) {
            
            oldUser.read((char*)&user[loc], sizeof(user[loc]));
            
            name = user[loc].useUsername();
            usert[loc].tsetUserName(name);
            
            pass = user[loc].usePassword();
            usert[loc].tsetPass(pass);
            
            acc = user[loc].useAcc();
            usert[loc].tsetAcc(acc);
            
            mail = user[loc].useMail();
            usert[loc].tsetMail(mail);
            
            cont = user[loc].useContact();
            usert[loc].tsetContact(cont);
            
            std::cout<<"Enter amount to be transferred : ";
            std::cin>>amt;
            transamt = amt;
            
            bal = user[loc].useBal();
            
            if(user[loc].useBal()<amt) {
                
                std::cout<<"\nLow Balance(Cannot transfer)...\n";
                transamt = 0;
                goto readc;
            } else {
                
                bal-=amt;
                usert[loc].tsetBal(bal);
            }
            
    readc:
           
            break;
        }
        
        newUser.write((char*)&usert[loc], sizeof(usert[loc]));
        newUser.close();
        oldUser.close();
        
        std::ifstream oldUser_("User", std::ios::in | std::ios::binary);
        std::ofstream newUser_("newUser", std::ios::out | std::ios::binary | std::ios::app);
        
        oldUser_.seekg(0);
        
        while(oldUser_.read((char*)&user[i], sizeof(user[i]))) {
            
            if(user[i].useUsername() != name) {
                
                newUser_.write((char*)&user[i], sizeof(user[i]));
            }
            
            i++;
            
            if(i>(posrec)) {
                
                break;
            }
        }
        
        oldUser_.close();
        newUser_.close();
        
        remove("User");
        rename("newUser", "User");
    
        if(transamt!=0) {
        
            std::ofstream add("Transact", std::ios::out | std::ios::app);
            
            auto time_now =      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            
            add<<"A user transferred some amount from his account...\n";
            add<<"Details of transferrer :\n";
            add<<"Time : "<<ctime(&time_now)<<"\n";
            add<<"Username : "<<name<<"\n";
            add<<"Amount : "<<transamt<<"\n";
            
            add.close();
            
            depTransAcc(transamt);
        }
}

void deleteAcc() {
    
    int i=0;
    
    std::ifstream oldUser_("User", std::ios::in | std::ios::binary);
    std::ofstream newUser_("newUser", std::ios::out | std::ios::binary | std::ios::app);
    
    oldUser_.seekg(0);
    
    while(oldUser_.read((char*)&user[i], sizeof(user[i]))) {
        
        if(i!=loc) {
            
            newUser_.write((char*)&user[i], sizeof(user[i]));
        }
        
        i++;
        
        if(i>(posrec)) {
            
            break;
        }
    }
    
    oldUser_.close();
    newUser_.close();
    
    remove("User");
    rename("newUser", "User");
    
    std::cout<<"Your account deleted successfully\n\n";
    
    std::ifstream rin("RecCount", std::ios::in | std::ios::binary);
    std::ofstream rout("tRecCount", std::ios::out | std::ios::binary | std::ios::app);
    
    while(!rin.eof()) {
        
        rin.read((char*)&rec, sizeof(rec));
        posrec = rec.reccount;
        posrec -=1;
        
        trec.reccount = posrec;
        
        rout.write((char*)&trec, sizeof(trec));
        
        rout.close();
        rin.close();
        break;
    }
    
    remove("RecCount");
    rename("tRecCount", "RecCount");
}

class Admin {
    
public:
    
    std::string admin;
    std::string pass;
    
public:
    
    void getUser() {
        
        std::cin>>admin;
        
    }
    
    void getPassword() {
        
        std::cin>>pass;
    }
    
    std::string useUsername() {
        
        return admin;
    }
    
    std::string usePassword() {
        
        return pass;
    }
}adm;

void adminView() {
    
    int i=0;
    
    std::ifstream rin("RecCount", std::ios::in | std::ios::binary);
    
    while(!rin.eof()) {
        
        rin.read((char*)&trec, sizeof(trec));
        posrec = trec.reccount;
        rin.close();
        break;
    }
    
    std::cout<<"\n";
    std::ifstream aduser("User", std::ios::in | std::ios::binary);
    
    while(aduser.read((char*)&user[i], sizeof(user[i]))) {
        
        std::cout<<"Name: "<<user[i].useUsername()<<"\n";
        std::cout<<"Account Number: "<<user[i].useAcc()<<"\n";
        std::cout<<"Email: "<<user[i].useMail()<<"\n";
        std::cout<<"Contact: "<<user[i].useContact()<<"\n";
        std::cout<<"Balance: "<<user[i].useBal()<<"\n";
        
        std::cout<<"\n";
        i++;
        
        if(i>(posrec)) {
            
            break;
        }
    }
    
    aduser.close();
}

void adminFetch() {
    
    std::ifstream rin("RecCount", std::ios::in | std::ios::binary);
    
    while(!rin.eof()) {
        
        rin.read((char*)&trec, sizeof(trec));
        posrec = trec.reccount;
        rin.close();
        break;
    }

recheck:
    
    int i=0;
    
    std::string fetch;
    bool che=false;
    
    std::cout<<"\n";
    
    std::cout<<"Enter the username to be fetched: ";
    std::cin>>fetch;
    
    std::ifstream userC("User", std::ios::in | std::ios::binary);
    
    userC.seekg(0);
    
    while(!userC.eof()) {
        
        userC.read((char*)&user[i], sizeof(user[i]));
        
        if(user[i].useUsername() == fetch) {
            
            std::cout<<"Name: "<<user[i].useUsername()<<"\n";
            std::cout<<"Account Number: "<<user[i].useAcc()<<"\n";
            std::cout<<"Email: "<<user[i].useMail()<<"\n";
            std::cout<<"Contact: "<<user[i].useContact()<<"\n";
            std::cout<<"Balance: "<<user[i].useBal()<<"\n";
            
            che = true;
            
            break;
        }
        i++;
        
        if(i>(posrec)) {
            
            break;
        }
    }
    
    userC.close();
    
    if(che == false) {
        
        std::cout<<"Not found, try again...\n";
        goto recheck;
    }
}

void adminTransView() {
    
    std::ifstream view("Transact", std::ios::in);
    
    if(!view) {
        
        std::cout<<"\nNo new transactions\n";
    }
    
    std::string str;
    
    while (std::getline(view, str)) {
        
      std::cout<<str<<"\n";
    }
    
    view.close();
}

void adminNotify() {
    
    std::ifstream view("Notify", std::ios::in);
    
    if(!view) {
        
        std::cout<<"\nNo new notifications\n";
    }
    
    std::string str;
    
    while (std::getline(view, str)) {
        
      std::cout<<str<<"\n";
    }
    
    view.close();
}

void adminReset() {
    
    remove("RecCount");
    remove("User");
    
    std::ofstream x("RecCount", std::ios::out | std::ios::binary | std::ios::app);

    rec.reccount = -1;

    x.write((char*)&rec, sizeof(rec));
    x.close();
}

int main() {
    
    int task, taskManage;
    
logout:
    
    std::cout<<"\t\t\t\t\t\t\t\t\t\t\t\tAccount Management\n\n";
    
    std::cout<<"\t\t\t\t\t\t\t\t\t\t\t   Log In as User/Admin\n\n";
    std::cout<<"Select one : \n\n";
    std::cout<<"1. User\n";
    std::cout<<"2. Admin\n";
    std::cout<<"3. Exit\n";
    
    std::cin>>taskManage;
    
    if(taskManage==1) {
        
        int log;
        
        std::cout<<"Sign in to your account :\n\n";
        std::cout<<"1. Sign Up\n";
        std::cout<<"2. Log In\n";
        std::cout<<"3. Exit\n";
        
        std::cin>>log;
        
        if(log==1) {
            
            createAcc();
            
            std::cout<<"\n\t\t\t\t\t\t\tLogin with your new account to access your data...\n\n";
            logAcc();
            
        } else if(log==2) {
            
            logAcc();
        } else {
            
            goto logout;
        }
        
disp:
        
        std::cout<<"Choose one of the given options :\n\n";
        
        std::cout<<"1. View existing Account\n";
        std::cout<<"2. Edit details of Account\n";
        std::cout<<"3. Withdraw\n";
        std::cout<<"4. Deposit\n";
        std::cout<<"5. Tranfer Money to an Account holder\n";
        std::cout<<"6. Delete Account\n";
        std::cout<<"7. Logout to homepage\n";
        std::cout<<"8. Exit\n";
        
        std::cin>>task;
        
        switch(task) {
                
            case 1: viewAcc();
                
                goto disp;
            
            case 2: editAcc();
                
                std::cout<<"Re-Login to view updated account... (For security)\n\n";
                
                goto logout;
                
            case 3: withdrawAcc();
                
                std::cout<<"Re-Login to view updated account... (For security)\n\n";
                
                goto logout;
                
            case 4: depositAcc();
                
                std::cout<<"Re-Login to view updated account... (For security)\n\n";
                
                goto logout;
                
            case 5: transferAcc();
                
                std::cout<<"Re-Login to view updated account... (For security)\n\n";
                
                goto logout;
                
            case 6: deleteAcc();
                
                goto logout;
                
            case 7: goto logout;
                
            case 8: exit(0);
        }
    } else if(taskManage==2) {
        
        int admm;
        
        std::cout<<"Sign in to your account :\n\n";
        std::cout<<"1. Log In\n";
        std::cout<<"2. Exit\n";
        
        std::cin>>admm;
        
        if(admm==1) {
            
            inpUs:
                
                std::ifstream userCheck("Admin", std::ios::in | std::ios::binary);
                std::string tuser, tpass;
                
                std::cout<<"Enter your Username: ";
                std::cin>>tuser;
                
                userCheck.seekg(0);
                
                while(!userCheck.eof()) {
                    
                    userCheck.read((char*)&adm, sizeof(adm));
                    
                    if(adm.useUsername()==tuser) {
                        
                    rep:
                        
                        std::cout<<"Enter your password: ";
                        std::cin>>tpass;
                        
                        if(adm.usePassword()==tpass) {
                            
                            std::cout<<"Log in succesful...\n";
                            userCheck.close();
                            goto end;
                        } else {
                            
                            std::cout<<"Try again...\n";
                            goto rep;
                        }
                    }
                }

                userCheck.close();
                
                std::cout<<"User not found as such, try again...\n";
                goto inpUs;
                
            end:
                std::cout<<"\n\n";
        } else {
            
            exit(0);
        }
        
re:
        
        int l;
        
        std::cout<<"Choose one of the given options :\n\n";
        std::cout<<"1. View all users\n";
        std::cout<<"2. Fetch details of a certain User\n";
        std::cout<<"3. Transaction details of user\n";
        std::cout<<"4. Latest Notifications related to all accounts\n";
        std::cout<<"5. Reset Account server(delete all data)\n";
        std::cout<<"6. Clear Transaction Data\n";
        std::cout<<"7. LogOut to homepage\n";
        std::cout<<"8. Exit\n";
        
        std::cin>>l;
        
        switch(l) {
                
            case 1: adminView();
                
                goto re;
                
            case 2: adminFetch();
                
                goto re;
                
            case 3: adminTransView();
                
                goto re;
                
            case 4: adminNotify();
                
                remove("Notify");
                
                goto re;
                
            case 5: adminReset();
                
                goto re;
            
            case 6: remove("Transact");
                
                std::cout<<"\nAll transaction data cleared\n";
                
                goto re;
                
            case 7:
                
                goto logout;
                
            case 8: exit(0);
        }
        
    } else {
        
        exit(0);
    }
}


