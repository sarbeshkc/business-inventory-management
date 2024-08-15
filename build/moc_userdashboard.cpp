/****************************************************************************
** Meta object code from reading C++ file 'userdashboard.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../userdashboard.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userdashboard.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSUserDashboardENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSUserDashboardENDCLASS = QtMocHelpers::stringData(
    "UserDashboard",
    "errorOccurred",
    "",
    "error",
    "totalInventoryItemsChanged",
    "lowStockItemsChanged",
    "totalInventoryValueChanged",
    "totalSalesChanged",
    "totalRevenueChanged",
    "totalCostChanged",
    "grossProfitChanged",
    "profitMarginChanged",
    "recentActivitiesChanged",
    "lowStockItemsListChanged",
    "monthlyProfitDataChanged",
    "expiringItemsChanged",
    "itemNearExpiry",
    "itemId",
    "itemName",
    "expiryDate",
    "refresh",
    "totalInventoryItems",
    "lowStockItems",
    "totalInventoryValue",
    "totalSales",
    "totalRevenue",
    "totalCost",
    "grossProfit",
    "profitMargin",
    "recentActivities",
    "lowStockItemsList",
    "monthlyProfitData",
    "expiringItems"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSUserDashboardENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
      12,  127, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  104,    2, 0x06,   13 /* Public */,
       4,    0,  107,    2, 0x06,   15 /* Public */,
       5,    0,  108,    2, 0x06,   16 /* Public */,
       6,    0,  109,    2, 0x06,   17 /* Public */,
       7,    0,  110,    2, 0x06,   18 /* Public */,
       8,    0,  111,    2, 0x06,   19 /* Public */,
       9,    0,  112,    2, 0x06,   20 /* Public */,
      10,    0,  113,    2, 0x06,   21 /* Public */,
      11,    0,  114,    2, 0x06,   22 /* Public */,
      12,    0,  115,    2, 0x06,   23 /* Public */,
      13,    0,  116,    2, 0x06,   24 /* Public */,
      14,    0,  117,    2, 0x06,   25 /* Public */,
      15,    0,  118,    2, 0x06,   26 /* Public */,
      16,    3,  119,    2, 0x06,   27 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      20,    0,  126,    2, 0x02,   31 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QDate,   17,   18,   19,

 // methods: parameters
    QMetaType::Void,

 // properties: name, type, flags
      21, QMetaType::Int, 0x00015001, uint(1), 0,
      22, QMetaType::Int, 0x00015001, uint(2), 0,
      23, QMetaType::Double, 0x00015001, uint(3), 0,
      24, QMetaType::Int, 0x00015001, uint(4), 0,
      25, QMetaType::Double, 0x00015001, uint(5), 0,
      26, QMetaType::Double, 0x00015001, uint(6), 0,
      27, QMetaType::Double, 0x00015001, uint(7), 0,
      28, QMetaType::Double, 0x00015001, uint(8), 0,
      29, QMetaType::QVariantList, 0x00015001, uint(9), 0,
      30, QMetaType::QVariantList, 0x00015001, uint(10), 0,
      31, QMetaType::QVariantList, 0x00015001, uint(11), 0,
      32, QMetaType::Int, 0x00015001, uint(12), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject UserDashboard::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSUserDashboardENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSUserDashboardENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSUserDashboardENDCLASS_t,
        // property 'totalInventoryItems'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'lowStockItems'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'totalInventoryValue'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'totalSales'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'totalRevenue'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'totalCost'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'grossProfit'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'profitMargin'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'recentActivities'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // property 'lowStockItemsList'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // property 'monthlyProfitData'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // property 'expiringItems'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<UserDashboard, std::true_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'totalInventoryItemsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lowStockItemsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'totalInventoryValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'totalSalesChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'totalRevenueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'totalCostChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'grossProfitChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'profitMarginChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recentActivitiesChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lowStockItemsListChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'monthlyProfitDataChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'expiringItemsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'itemNearExpiry'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDate &, std::false_type>,
        // method 'refresh'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void UserDashboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserDashboard *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->totalInventoryItemsChanged(); break;
        case 2: _t->lowStockItemsChanged(); break;
        case 3: _t->totalInventoryValueChanged(); break;
        case 4: _t->totalSalesChanged(); break;
        case 5: _t->totalRevenueChanged(); break;
        case 6: _t->totalCostChanged(); break;
        case 7: _t->grossProfitChanged(); break;
        case 8: _t->profitMarginChanged(); break;
        case 9: _t->recentActivitiesChanged(); break;
        case 10: _t->lowStockItemsListChanged(); break;
        case 11: _t->monthlyProfitDataChanged(); break;
        case 12: _t->expiringItemsChanged(); break;
        case 13: _t->itemNearExpiry((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QDate>>(_a[3]))); break;
        case 14: _t->refresh(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UserDashboard::*)(const QString & );
            if (_t _q_method = &UserDashboard::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::totalInventoryItemsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::lowStockItemsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::totalInventoryValueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::totalSalesChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::totalRevenueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::totalCostChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::grossProfitChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::profitMarginChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::recentActivitiesChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::lowStockItemsListChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::monthlyProfitDataChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::expiringItemsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)(int , const QString & , const QDate & );
            if (_t _q_method = &UserDashboard::itemNearExpiry; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<UserDashboard *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->totalInventoryItems(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->lowStockItems(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->totalInventoryValue(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->totalSales(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->totalRevenue(); break;
        case 5: *reinterpret_cast< double*>(_v) = _t->totalCost(); break;
        case 6: *reinterpret_cast< double*>(_v) = _t->grossProfit(); break;
        case 7: *reinterpret_cast< double*>(_v) = _t->profitMargin(); break;
        case 8: *reinterpret_cast< QVariantList*>(_v) = _t->recentActivities(); break;
        case 9: *reinterpret_cast< QVariantList*>(_v) = _t->lowStockItemsList(); break;
        case 10: *reinterpret_cast< QVariantList*>(_v) = _t->monthlyProfitData(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->expiringItems(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *UserDashboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserDashboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSUserDashboardENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UserDashboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void UserDashboard::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UserDashboard::totalInventoryItemsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void UserDashboard::lowStockItemsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void UserDashboard::totalInventoryValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void UserDashboard::totalSalesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void UserDashboard::totalRevenueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void UserDashboard::totalCostChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void UserDashboard::grossProfitChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void UserDashboard::profitMarginChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void UserDashboard::recentActivitiesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void UserDashboard::lowStockItemsListChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void UserDashboard::monthlyProfitDataChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void UserDashboard::expiringItemsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void UserDashboard::itemNearExpiry(int _t1, const QString & _t2, const QDate & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_WARNING_POP
