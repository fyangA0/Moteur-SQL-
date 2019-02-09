#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "table.h"

using namespace std; 

Table::Table()
{}
Table::Table(string fileName) {
    ifstream stream(fileName.c_str());
    if (stream)
    {
        nomTable=Table::getFileName(fileName);
        nomAttributs = TabString(stream);
        valeurAttributs = MatriceString(stream);
    }
    else 
        exit(1);
}

Table::Table(const Table& tab1,const Table& tab2)
    :nomTable(tab1.nomTable+"JOIN"+tab2.nomTable),nomAttributs(tab1.nomAttributs,tab2.nomAttributs),valeurAttributs(tab1.valeurAttributs,tab2.valeurAttributs){
        
}


void Table::print() {
    size_t *tabMax= new size_t[nomAttributs.getSize()];
    size_t max,somme=0;
    string sep,space;
    for(size_t i= 0 ; i < nomAttributs.getSize(); ++i) {
        max = nomAttributs[i].size();
        for(size_t j=0 ; j < valeurAttributs.getSize();++j)
        {
            max = (valeurAttributs[j][i].size() < max ? max : valeurAttributs[j][i].size()); 
        }
        tabMax[i]=max;
        somme+=tabMax[i];
    }
    
    cout << endl;
    
    /* Affichages des noms des attributs*/
    cout << "| ";       
    for(size_t i = 0; i < nomAttributs.getSize(); i++){
        cout << nomAttributs[i] ;
        space = string(tabMax[i]-nomAttributs[i].size() + 1,' ');
        cout << space <<" | " ;
    }
    cout << endl;
    /* affichage du séparateur */
    sep = string(somme+(nomAttributs.getSize()*4)+1,'-');
    cout << sep<< endl;
    /* Affichages des valeurs des attributs */
    for(size_t i = 0; i < valeurAttributs.getSize(); i++) {
        cout << "| ";
        for(size_t j = 0; j < valeurAttributs[i].getSize() ; j++){
            cout << valeurAttributs[i][j];
            space = string(tabMax[j]-valeurAttributs[i][j].size()+1,' ');
            cout << space << " | ";
        }
        cout << endl;
    }
    cout << sep << endl;
    delete[] tabMax;
    
}

string Table::getNomTable(){
    return nomTable;
}

const TabString& Table::getNomAttributs() const{
    return nomAttributs;
}
const MatriceString& Table::getValeurAttributs() const{
    return valeurAttributs;
}

Table Table::projection(TabString attributs) const{
    return *this;
}
Table Table::selection(string condition) const{
    return *this;
}
Table Table::jointure(const Table& tab1,const Table& tab2) const{
    return Table(tab1,tab2);
}

/*
 * Get File Name from a Path with or without extension
 */
string Table::getFileName(string filePath, bool withExtension, char seperator) {
	/* Le dernièr point trouvé */
	size_t point = filePath.rfind(".");
    size_t sepPos = filePath.rfind(seperator);    
    // Séparateur trouver
	if(sepPos != string::npos)
        return filePath.substr(sepPos + 1,(withExtension || point == string::npos ? 1 : point) - sepPos -1);
    // Séparateur non trouver
    return filePath.substr(0,(withExtension || point == string::npos ? filePath.size() : point));
}

/*
 *  Affichage de la table sur un flux de sortie
*/
ostream& operator<<(ostream& stream,const Table& tab) {
    size_t *tabMax= new size_t[tab.getNomAttributs().getSize()];
    size_t max,somme=0;
    string sep,space;
    for(size_t i= 0 ; i < tab.getNomAttributs().getSize(); ++i) {
        max = tab.getNomAttributs()[i].size();
        for(size_t j=0 ; j < tab.getValeurAttributs().getSize();++j)
        {
            max = (tab.getValeurAttributs()[j][i].size() < max ? max : tab.getValeurAttributs()[j][i].size()); 
        }
        tabMax[i]=max;
        somme+=tabMax[i];
    }
    
    stream << endl;
    
    /* Affichages des noms des attributs*/
    stream << "| ";       
    for(size_t i = 0; i < tab.getNomAttributs().getSize(); i++){
        stream << tab.getNomAttributs()[i] ;
        space = string(tabMax[i]-tab.getNomAttributs()[i].size() + 1,' ');
        stream << space <<" | " ;
    }
    stream << endl;
    /* affichage du séparateur */
    sep = string(somme+(tab.getNomAttributs().getSize()*4)+1,'-');
    stream << sep<< endl;
    /* Affichages des valeurs des attributs */
    for(size_t i = 0; i < tab.getValeurAttributs().getSize(); i++) {
        stream << "| ";
        for(size_t j = 0; j < tab.getValeurAttributs()[i].getSize() ; j++){
            stream << tab.getValeurAttributs()[i][j];
            space = string(tabMax[j]-tab.getValeurAttributs()[i][j].size()+1,' ');
            stream << space << " | ";
        }
        stream << endl;
    }
    stream << sep << endl;
    delete[] tabMax;

    return stream;   
}
