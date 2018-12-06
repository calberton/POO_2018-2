#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Passageiro{
    string nome;
    int idade;

    Passageiro(string nome, int idade){
        this->nome = nome;
        this->idade = idade;
    }
};

struct Topic{
    int preferencial;
    vector< Passageiro* > poltronas;

    Topic(int lotacaoMax = 0, int preferencial = 0):poltronas(lotacaoMax, nullptr){
        this->preferencial = preferencial;
    }

    bool out(string nome){
        for(int i = 0; i < (int)poltronas.size(); i++){
            if(poltronas[i] != nullptr && poltronas[i]->nome == nome){
                delete(poltronas[i]);
                poltronas[i] = nullptr;
                return true;
            }
        }
        cout << "Fail : não tem ninguem com esse nome aqui" << endl;
        return false;
    }


    bool in(string nome, int idade){
        if(idade < 0)
            idade=0;
        for(Passageiro *p : poltronas){
            if(p != nullptr && p->nome == nome){
                cout << "Erro: essa pessoa ja esta na topic" << endl;
                return false;
            }
        }

        if(idade > 60){
            for(int i = 0; i < (int)poltronas.size(); i++){
                if(poltronas[i] == nullptr){
                    poltronas[i] = new Passageiro(nome, idade);
                    return true;
                }
            }
            cout << "Erro: Topic lotada" << endl;
            return false;
        }

        for(int i = this->preferencial; i < (int)poltronas.size(); i++){
            if(poltronas[i] == nullptr){
                poltronas[i] = new Passageiro(nome, idade);
                return true;
            }
        }

        for(int i = 0; i < this->preferencial; i++){
            if(poltronas[i] == nullptr){
                poltronas[i] = new Passageiro(nome, idade);
                return true;
            }
        }

        cout << "Erro: Topic lotada" << endl;
        return false;
    }

    string show(){
        stringstream ss;
        ss << "[";
        for(int i = 0; i < (int)poltronas.size(); i++){
            ss << (i < preferencial ? " @" : " =");
            if(poltronas[i] != nullptr){
                ss << poltronas[i]->nome << ":" << poltronas[i]->idade;
            }
        }
        ss << " ]";
        return ss.str();
    }
};

struct Controller{
    Topic top;

    string resposta(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
        if(op == "help"){
            out << "show; init (LT,P); in (N,,I); out (N);";
        }else if(op == "show"){
            out << top.show();
        }else if(op == "init"){
            int lotacaoMax, preferencial;
            in >> lotacaoMax >> preferencial;
            top = Topic(lotacaoMax, preferencial);
            out << "done";
        }else if(op == "in"){
            string nome;
            int idade;
            in >> nome >> idade;
            if(top.in(nome, idade)){
                out << "done";
            }
        }else if(op == "out"){
            string nome;
            in >> nome;
            if(top.out(nome)){
                out << "done";
            }
        }

        return out.str();
    }


    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "fim"){
                return;
            }
            cout << "   " << resposta(line) << endl;
        }
    }
};


int main(){
    Controller c;
    c.exec();
    return 0;
}
