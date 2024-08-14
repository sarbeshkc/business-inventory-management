/****************************************************************************
** Meta object code from reading C++ file 'salesmodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../salesmodel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'salesmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSSalesModelENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSSalesModelENDCLASS = QtMocHelpers::stringData(
    "SalesModel",
    "errorOccurred",
    "",
    "error",
    "totalSalesChanged",
    "revenueThisMonthChanged",
    "totalRevenueChanged",
    "maxMonthlySalesChanged",
    "monthlySalesDataChanged",
    "topProductsChanged",
    "addSale",
    "itemId",
    "quantity",
    "price",
    "category",
    "supplierName",
    "supplierAddress",
    "searchSales",
    "searchText",
    "sortSales",
    "column",
    "Qt::SortOrder",
    "order",
    "refresh",
    "refreshAnalytics",
    "totalSales",
    "revenueThisMonth",
    "totalRevenue",
    "maxMonthlySales",
    "monthlySalesData",
    "topProducts"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSalesModelENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       6,  118, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   86,    2, 0x06,    7 /* Public */,
       4,    0,   89,    2, 0x06,    9 /* Public */,
       5,    0,   90,    2, 0x06,   10 /* Public */,
       6,    0,   91,    2, 0x06,   11 /* Public */,
       7,    0,   92,    2, 0x06,   12 /* Public */,
       8,    0,   93,    2, 0x06,   13 /* Public */,
       9,    0,   94,    2, 0x06,   14 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      10,    6,   95,    2, 0x02,   15 /* Public */,
      17,    1,  108,    2, 0x02,   22 /* Public */,
      19,    2,  111,    2, 0x02,   24 /* Public */,
      23,    0,  116,    2, 0x02,   27 /* Public */,
      24,    0,  117,    2, 0x02,   28 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,   14,   15,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 21,   20,   22,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      25, QMetaType::Int, 0x00015001, uint(1), 0,
      26, QMetaType::Double, 0x00015001, uint(2), 0,
      27, QMetaType::Double, 0x00015001, uint(3), 0,
      28, QMetaType::Double, 0x00015001, uint(4), 0,
      29, QMetaType::QVariantList, 0x00015001, uint(5), 0,
      30, QMetaType::QVariantList, 0x00015001, uint(6), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject SalesModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_CLASSSalesModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSalesModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSalesModelENDCLASS_t,
        // property 'totalSales'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'revenueThisMonth'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'totalRevenue'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'maxMonthlySales'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'monthlySalesData'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // property 'topProducts'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SalesModel, std::true_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'totalSalesChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'revenueThisMonthChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'totalRevenueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'maxMonthlySalesChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'monthlySalesDataChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'topProductsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addSale'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'searchSales'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'sortSales'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::SortOrder, std::false_type>,
        // method 'refresh'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshAnalytics'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SalesModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SalesModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->totalSalesChanged(); break;
        case 2: _t->revenueThisMonthChanged(); break;
        case 3: _t->totalRevenueChanged(); break;
        case 4: _t->maxMonthlySalesChanged(); break;
        case 5: _t->monthlySalesDataChanged(); break;
        case 6: _t->topProductsChanged(); break;
        case 7: { bool _r = _t->addSale((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->searchSales((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->sortSales((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Qt::SortOrder>>(_a[2]))); break;
        case 10: _t->refresh(); break;
        case 11: _t->refreshAnalytics(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SalesModel::*)(const QString & );
            if (_t _q_method = &SalesModel::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SalesModel::*)();
            if (_t _q_method = &SalesModel::totalSalesChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SalesModel::*)();
            if (_t _q_method = &SalesModel::revenueThisMonthChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SalesModel::*)();
            if (_t _q_method = &SalesModel::totalRevenueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SalesModel::*)();
            if (_t _q_method = &SalesModel::maxMonthlySalesChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SalesModel::*)();
            if (_t _q_method = &SalesModel::monthlySalesDataChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SalesModel::*)();
            if (_t _q_method = &SalesModel::topProductsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SalesModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->totalSales(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->revenueThisMonth(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->totalRevenue(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->maxMonthlySales(); break;
        case 4: *reinterpret_cast< QVariantList*>(_v) = _t->monthlySalesData(); break;
        case 5: *reinterpret_cast< QVariantList*>(_v) = _t->topProducts(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *SalesModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SalesModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSalesModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int SalesModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SalesModel::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SalesModel::totalSalesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SalesModel::revenueThisMonthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SalesModel::totalRevenueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SalesModel::maxMonthlySalesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SalesModel::monthlySalesDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SalesModel::topProductsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
