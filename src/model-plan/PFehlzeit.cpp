/* 
 * File:   PFehlzeit.cpp
 * Author: Yannik
 * 
 * Created on October 6, 2015, 11:14 PM
 */

#include "PFehlzeit.h"

PFehlzeit::PFehlzeit(PMessdiener* _mini, wxDateTime _datum_beginn, wxDateTime _datum_ende)
: mini(_mini), datum_beginn(_datum_beginn), datum_ende(_datum_ende) {

}