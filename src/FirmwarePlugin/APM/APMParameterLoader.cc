/*=====================================================================
 
 QGroundControl Open Source Ground Control Station
 
 (c) 2009 - 2014 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 
 This file is part of the QGROUNDCONTROL project
 
 QGROUNDCONTROL is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 QGROUNDCONTROL is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.
 
 ======================================================================*/

/// @file
///     @author Don Gagne <don@thegagnes.com>

#include "APMParameterLoader.h"
#include "QGCApplication.h"
#include "QGCLoggingCategory.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

QGC_LOGGING_CATEGORY(APMParameterLoaderLog, "APMParameterLoaderLog")

bool APMParameterLoader::_parameterMetaDataLoaded = false;
QMap<QString, FactMetaData*> APMParameterLoader::_mapParameterName2FactMetaData;

APMParameterLoader::APMParameterLoader(AutoPilotPlugin* autopilot, Vehicle* vehicle, QObject* parent) :
    ParameterLoader(autopilot, vehicle, parent)
{
    Q_ASSERT(vehicle);
}

/// Converts a string to a typed QVariant
///     @param string String to convert
///     @param type Type for Fact which dictates the QVariant type as well
///     @param convertOk Returned: true: conversion success, false: conversion failure
/// @return Returns the correctly type QVariant
QVariant APMParameterLoader::_stringToTypedVariant(const QString& string, FactMetaData::ValueType_t type, bool* convertOk)
{
    QVariant var(string);

    int convertTo = QVariant::Int; // keep compiler warning happy
    switch (type) {
        case FactMetaData::valueTypeUint8:
        case FactMetaData::valueTypeUint16:
        case FactMetaData::valueTypeUint32:
            convertTo = QVariant::UInt;
            break;
        case FactMetaData::valueTypeInt8:
        case FactMetaData::valueTypeInt16:
        case FactMetaData::valueTypeInt32:
            convertTo = QVariant::Int;
            break;
        case FactMetaData::valueTypeFloat:
            convertTo = QMetaType::Float;
            break;
        case FactMetaData::valueTypeDouble:
            convertTo = QVariant::Double;
            break;
    }
    
    *convertOk = var.convert(convertTo);
    
    return var;
}

/// Load Parameter Fact meta data
///
/// The meta data comes from firmware parameters.xml file.
void APMParameterLoader::loadParameterFactMetaData(void)
{
    if (_parameterMetaDataLoaded) {
        return;
    }
    _parameterMetaDataLoaded = true;

    // FIXME: NYI

    // Static meta data should load all MAV_TYPEs from single meta data file in such a way that the loader
    // has multiple sets of static meta data
}

void APMParameterLoader::clearStaticData(void)
{
    foreach(QString parameterName, _mapParameterName2FactMetaData.keys()) {
        delete _mapParameterName2FactMetaData[parameterName];
    }
    _mapParameterName2FactMetaData.clear();
    _parameterMetaDataLoaded = false;
}

/// Override from FactLoad which connects the meta data to the fact
void APMParameterLoader::_addMetaDataToFact(Fact* fact)
{
    // FIXME: Will need to switch here based on _vehicle->firmwareType() to pull right set of meta data

    // Use generic meta data
    ParameterLoader::_addMetaDataToFact(fact);
}
