#include<iostream>
#include <cstring>
using namespace std;

class Avtomobil{
private:
    char n[20];
    char brende[20];
    char model[20];
    void copy(const Avtomobil&a){
        strcpy(this->n,a.n);
        strcpy(this->brende,a.brende);
        strcpy(this->model,a.model);
    }
public:
    Avtomobil(){
        strcpy(n,"");
        strcpy(brende,"");
        strcpy(model,"");
    }
    Avtomobil(char *n,char *brend,char *model){
        strcpy(this->n,n);
        strcpy(this->brende,brend);
        strcpy(this->model,model);
    }
    Avtomobil(const Avtomobil&a){
        copy(a);
    }
    Avtomobil&operator=(const Avtomobil&a){
        if(this!=&a){
            copy(a);
        }
        return *this;
    }
    ~Avtomobil(){}
    void pecati(){
        cout << n <<" "<< brende << " " << model << endl;
    }



};
class ParkingPlac{
private:
    char adresa[20];
    char *id;
    int cena;
    int zarabotka;
    Avtomobil *avtomobil;
    int parkirani;

    void copy(const ParkingPlac&p){
        strcpy(this->adresa,p.adresa);
        this->id=new char[strlen(p.id)+1];
        strcpy(this->id,p.id);
        this->cena=p.cena;
        this->zarabotka=p.zarabotka;
        this->avtomobil=new Avtomobil[p.parkirani];
        for(int i=0;i<p.parkirani;i++){
            this->avtomobil[i]=p.avtomobil[i];
        }
        this->parkirani=p.parkirani;
    }
public:
    ParkingPlac(){
        strcpy(this->adresa,"");
        this->id=new char[1];
        strcpy(this->id,"");
        this->cena=0;
        this->zarabotka=0;
        this->avtomobil=new Avtomobil[1];
        this->parkirani=0;
    }
    ParkingPlac(char *adresa,char *id,int cena){
        strcpy(this->adresa,adresa);
        this->id=new char[strlen(id)+1];
        strcpy(this->id,id);
        this->cena=cena;
        this->zarabotka=0;
        this->avtomobil=new Avtomobil[1];
        this->parkirani=0;
    }
    ParkingPlac(const ParkingPlac&p){
        copy(p);
    }
    ParkingPlac&operator=(const ParkingPlac&p){
        if(this!=&p){
            delete[]id;
            delete[]avtomobil;
            copy(p);
        }
        return *this;
    }
    ~ParkingPlac(){
        delete[]id;
        delete[]avtomobil;
    }

    char *getId(){
        return id;
    }
    void platiCasovi(int casovi){
        zarabotka+=casovi*cena;
    }

    bool daliIstaAdresa(ParkingPlac p){
        return strcpy(this->adresa,p.adresa)==0;
    }

    void parkirajVozilo(const Avtomobil &novoVozilo){
        Avtomobil*tmp=new Avtomobil[parkirani+1];
        for(int i=0;i<parkirani;i++){
            tmp[i]=avtomobil[i];
        }
        tmp[parkirani++]=novoVozilo;
        delete[]avtomobil;
        avtomobil=tmp;
    }
    void pecati() const {
        if (zarabotka != 0) {
            cout << id << " " << adresa << " - " << zarabotka << " denari" << endl;
        } else {
            cout << id << " " << adresa << endl;
        }
    }

    void pecatiParkiraniVozila(){
        cout<<"Vo parkingot se parkirani slednite vozila:"<<endl;
        for(int i=0;i<parkirani;i++){
            cout<<i+1<<".";
            avtomobil[i].pecati();
        }
    }

};

int main(){

	ParkingPlac p[100];
	int n,m;
	char adresa[50],id[50];
	int brojcasovi,cenacas;
	cin>>n;
	if(n > 0){


		for (int i=0;i<n;i++){
	        cin.get();
			cin.getline(adresa,50);
			cin>>id>>cenacas;

			ParkingPlac edna(adresa,id,cenacas);

	        p[i]=edna;
		}

		//plakjanje
		cin>>m;
		for (int i=0;i<m;i++){

			cin>>id>>brojcasovi;

	        int findId=false;
	        for (int j=0;j<m;j++){
	            if (strcmp(p[j].getId(),id)==0){
	                p[j].platiCasovi(brojcasovi);
	                findId=true;
	            }
	        }
			if (!findId)
	        cout<<"Ne e platen parking. Greshen ID."<<endl;
		}

	    cout<<"========="<<endl;
	    ParkingPlac pCentar("Cvetan Dimov","C10",80);
		for (int i=0;i<n;i++)
	        if (p[i].daliIstaAdresa(pCentar))
	            p[i].pecati();
	} else {

		ParkingPlac najdobarPlac("Mars", "1337", 1);
	    int brVozila;
	    cin >> brVozila;
	    for(int i = 0; i < brVozila; ++i){

	    	char boja[20];
	    	char brend[20];
	    	char model[20];

	    	cin >> boja >> brend >> model;
	    	Avtomobil novAvtomobil(boja, brend, model);
	    	najdobarPlac.parkirajVozilo(novAvtomobil);
	    }
	    if(brVozila != 0)
	    najdobarPlac.pecatiParkiraniVozila();

	}
}
