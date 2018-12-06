#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Fone{
private:
    string label;
    string numero;
public:
    Fone(string label = "", string numero = ""){
        this->label = label;
        this->numero = numero;
    }

    bool validade(){
        size_t findCarcter = this->numero.find_first_not_of("0123456789().");
        if(findCarcter != this->numero.npos){
            return false;
        }
        return true;
    }

    string toString(){
        stringstream ss;
        ss << label << ":" << numero;
        return ss.str();
    }

};

class Contato{
private:
    string nome;
    vector <Fone> telefones;
public:
    Contato(string nome = "vazio"){
        this->nome = nome;
    }

    bool addFone(Fone fone){
        if(fone.validade()){
            telefones.push_back(fone);
            return true;
        }
        return false;
    }

    void rmFone(int ind){
        telefones.erase(telefones.begin() + ind);
    }

    void retiraTudo(){
        for(auto posicao : telefones){
            telefones.pop_back();
        }
    }

    void update(string line){
        Fone f;
        stringstream ss(line);
        string naoPreciso, name, word;
        ss >> naoPreciso; //update
        ss >> name;
        this->nome = name;
        this->retiraTudo();
        string label, fone;
        while (ss >> word){
            stringstream ss(word);
            getline(ss, label, ':');
            getline(ss, fone);
            f = Fone(label, fone);
            if(f.validade()){
                telefones.push_back(f);
            }
        }
    }

    string toString(){
        stringstream ss;
        ss << nome << "=>";
        for(int i = 0; i < (int)telefones.size(); i++){
            ss << "[" << i << ":" << telefones[i].toString() << "]";
        }
        return ss.str();
    }
};

struct Controller{
    Contato contato;

    string funcoes(string line){
        stringstream in(line);
        stringstream out;
        string op;
        in >> op;
        if(op == "help"){
            out << "show; init; add; rm; update";//init(nome); add(label,numero); rm(indice); update(nome, telefones)
        }else if(op == "show"){
            out << contato.toString();
        }else if(op == "init"){
            string nome;
            in >> nome;
            contato = Contato(nome);
            out << "done";
        }else if(op == "add"){
            string label, numero;
            in >> label >> numero;
            if(contato.addFone(Fone(label,numero))){
                out << "done";
            }else{
                out << "fail: numero invalido";
            }
        }else if(op == "rm"){
            int ind;
            in >> ind;
            contato.rmFone(ind);
            out << "done";
        }else if(op == "update"){
            contato.update(in.str());
            out << "done";
        }

        return out.str();
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "fim"){
                break;
            }
            cout << "  " << funcoes(line) << endl;
        }
    }
};

int main(){
    Controller c;
    c.exec();
    return 0;
}
