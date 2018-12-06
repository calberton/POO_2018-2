#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

template<typename T>
class Repositorio{
    map<string, T> rep;
public:
    string tipo;
    Repositorio(string tipo = ""){
        this->tipo = tipo;
    }
    bool existe(string k){
        if(rep.count(k) != 0)
            return true;
        return false;
    }
    void add(string k, T t){
        if(existe(k))
            throw tipo + " " + k + " já existe";
        rep[k] = t;
    }
    T& get(string k){
        auto it = rep.find(k);
        if(it == rep.end())
            throw tipo + " " + k + " não existe";
        return it->second;
    }
    vector<T> getValues(){
        vector<T> values;
        for(auto& elem : rep)
            values.push_back(elem.second);
        return values;
    }
    vector<string> getKeys(){
        vector<string> keys;
        for(auto& elem : rep)
            keys.push_back(elem.first);
        return keys;
    }
    void remove(string k){
        auto it = rep.find(k);
        if(it == rep.end())
            throw tipo + " " + k + " não existe";
        rep.erase(k);
    }

};

class Aluno{
public:
    string matricula;
    string curso;
    string nome;
    Aluno(string matricula = "", string curso = "", string nome = ""){
        this->curso = curso;
        this->matricula =matricula;
        this->nome = nome;
    }
    friend ostream& operator<<(ostream &os, Aluno aluno);
};
    ostream& operator<<(ostream &os, Aluno aluno){
        os << aluno.matricula << ":" << aluno.curso
        << ":" << aluno.nome;
        return os;
    }

class Professor{
    public:
        string nome;
        string siape;
        Professor(string nome = "", string siape = ""){
            this->nome = nome;
            this->siape = siape;
        }
        friend ostream& operator<<(ostream &os, Professor prof);
};
    ostream& operator<<(ostream &os, Professor prof){
        os << prof.nome << ":" << prof.siape;
        return os;
    }
class Disciplina{
    public:
    string codigo;
    string nome;
    Disciplina(string cod = "", string nome = ""){
        this->codigo = cod;
        this->nome = nome;
    }
    friend ostream& operator<<(ostream &os, Disciplina dis);
};
    ostream& operator<<(ostream &os, Disciplina dis){
        os << dis.codigo << ":" << dis.nome;
        return os;
    }
template<typename V>
V read(stringstream& ss){
    V v;
    ss >> v;
    return v;
}

class Controller{
public:
    Repositorio<Aluno> repAlu;
    Repositorio<Professor> repProf;
    Repositorio<Disciplina> repDis;

    Controller():
    repAlu("Aluno"), repProf("Professor"), repDis("Disciplina")
    {}

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;
        if(op == "help"){
            cout << " AddAlu; addProf; addDis; showAlu; showProf; showDis; getAlu; getProf; getDis; rmAlu; rmProf; rmDis; help; end"<< endl;
        }else if(op == "addAlu"){
                string matri, curso, nome;
                ss >> matri >> curso;
                getline(ss, nome);
                repAlu.add(matri, Aluno(matri,curso,nome));
                cout<< "done" <<endl;
        }else if(op == "addProf"){
                string siape, nome;
                ss >> siape;
                getline(ss, nome);
                repProf.add(siape, Professor(siape,nome));
                cout<< "done" <<endl;
        }else if(op == "addDis"){
            string cod, nome;
            ss >> cod;
            getline(ss, nome);
            repDis.add(cod, Disciplina(cod,nome));
            cout<< "done" <<endl;
        }
        else if(op == "showAlu"){
            for(auto elem : repAlu.getValues())
                cout << elem << endl;
            cout<< "done" <<endl;
        }
        else if(op == "showProf"){
            for(auto elem : repProf.getValues())
                cout << elem << endl;
            cout<< "done" <<endl;
        }
        else if(op == "showDis"){
            for(auto elem : repDis.getValues())
                cout << elem << endl;
        }else if(op == "getAlu"){
            string chave;
            ss >> chave;
            if(repAlu.existe(chave)){
                cout << repAlu.get(chave) << endl;
                cout<< "done" <<endl;
            }else
                cout << "fail: aluno " << chave << " não existe" << endl;
        }else if(op == "getProf"){
            string chave;
            ss >> chave;
            if(repProf.existe(chave)){
                cout << repProf.get(chave) << endl;
                cout<< "done" <<endl;
            }else
                cout << "fail: professor " << chave << " não existe" << endl;
        }else if(op == "getDis"){
            string chave;
            ss >> chave;
            if(repDis.existe(chave)){
                cout << repDis.get(chave) << endl;
                cout<< "done" <<endl;
            }else
                cout << "fail: disciplina " << chave << " não existe" << endl;
        }else if(op == "rmAlu"){
            string chave;
            ss >> chave;
            if(repAlu.existe(chave)){
                repAlu.remove(chave);
                cout<< "done" <<endl;
            }else
                cout << "fail: aluno " << chave << " não existe" << endl;
        }else if(op == "rmProf"){
            string chave;
            ss >> chave;
            if(repProf.existe(chave)){
                repProf.remove(chave);
                cout<< "done" <<endl;
            }else
                cout << "fail: professor " << chave << " não existe" << endl;
        }else if(op == "rmDis"){
            string chave;
            ss >> chave;
            if(repDis.existe(chave)){
                repDis.remove(chave);
                cout<< "done" <<endl;
            }else
                cout << "fail: disciplina " << chave << " não existe" << endl;
        }
        else
            cout << "Comando inválido" << endl;
    }

    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "fim")
                break;
            try{
                shell(line);
            }catch(string s){
                cout << s << endl;
            }
        }
    }
};

int main(){
    Controller c;
    c.exec();
    return 0;
}
