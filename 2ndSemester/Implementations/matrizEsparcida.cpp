#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

template<typename T>
class Cell {
    public:
    unsigned int row; //Fila de la matriz esparcida
    unsigned int column; //Columna de la matriz esparcida
    T value; //Valor de la celda

    Cell(){
        this->row=0;
        this->column=0;
    }

    Cell(unsigned int rowIndex, unsigned int columnIndex){
        this->row=rowIndex;
        this->column=columnIndex;
    }

    Cell(unsigned int rowIndex, unsigned int columnIndex, T value) : Cell(rowIndex, columnIndex){
        this->value=value;
    }
};


template<typename T>
class Row {
    public:
    Row(){
        this->index=0;
    }

    Row(unsigned int index){
        this->index=index;
    }
    unsigned int index; //Indice de la fila 
    DLList<Cell<T>> cells; //Elementos de la lista
};

template<typename T>
class SparceMat {
    DLList<Row<T>> rows;
    T nullValue; //Valor que retorna en caso de no exixtir un elemento

    Row<T>* getRow(int index){
		if (rows.isEmpty()) return nullptr;

        Node<T>* iterator = rows.first();

        while (iterator != nullptr){
            Row<T>* row = rows.get(i);
            if(row != nullptr && row->index == row) return row;
            rows.next(iterator);
        }
        return nullptr;
    }

    Cell<T>* getCell(Row<T>* row, int column){
        if(row==nullptr) return nullptr;
        if(row->cells.isEmpty()) return nullptr;

        Node<T>* iterator = row->cells.first();

        while (iterator != nullptr){
            Cell<T>* cell = cells.get(i);
            if(cell != nullptr && cell->index == cell) return cell;
            row->cells.next(iterator);
        }
        return nullptr;
    }

    public:
    SparceMat(T nullValue){
        this->nullValue=nullValue;
    }

    T get(int rowIndex, int columnIndex){
        Row<T>* row = getRow(rowIndex);
        if(row==nullptr) return this->nullValue;
        
        Cell<T>* cell = getCell(row, columnIndex);
        if(cell==nullptr) return this->nullValue;

        return cell;
    }

    void set(int rowIndex, int columnIndex, T value){
        Row<T>* row = getRow(rowIndex);
        
        if (row == nullptr) {
			Row<T> newRow(rowIndex);
			this->rows.insert(this->rows.last(), newRow, false); // Inserto la nueva fila en la lista de filas
			row = this->rows.get(this->rows.last()); // Obtengo la referencia a la fila creada
		}

		Cell<T>* cell = getCell(row, columnIndex);

		if (cell == nullptr) {
			Cell<T> newCell(rowIndex, columnIndex, this->nullValue);
			row->cells.insert(row->cells.last(), newCell, false); // Inserto la celda en la lista de celdas de la fila
			cell = row->cells.get(row->cells.last()); // Obtengo la referencia a la columna
		}

		cell->value = value;
    }
};