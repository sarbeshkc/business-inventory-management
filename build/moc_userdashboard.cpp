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
    "profitMarginChanged",
    "recentActivitiesChanged",
    "refresh",
    "totalInventoryItems",
    "lowStockItems",
    "totalInventoryValue",
    "totalSales",
    "totalRevenue",
    "profitMargin",
    "recentActivities"
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
       9,   14, // methods
       7,   79, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    8 /* Public */,
       4,    0,   71,    2, 0x06,   10 /* Public */,
       5,    0,   72,    2, 0x06,   11 /* Public */,
       6,    0,   73,    2, 0x06,   12 /* Public */,
       7,    0,   74,    2, 0x06,   13 /* Public */,
       8,    0,   75,    2, 0x06,   14 /* Public */,
       9,    0,   76,    2, 0x06,   15 /* Public */,
      10,    0,   77,    2, 0x06,   16 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,   78,    2, 0x02,   17 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::Int, 0x00015001, uint(1), 0,
      13, QMetaType::Int, 0x00015001, uint(2), 0,
      14, QMetaType::Double, 0x00015001, uint(3), 0,
      15, QMetaType::Int, 0x00015001, uint(4), 0,
      16, QMetaType::Double, 0x00015001, uint(5), 0,
      17, QMetaType::Double, 0x00015001, uint(6), 0,
      18, QMetaType::QVariantList, 0x00015001, uint(7), 0,

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
        // property 'profitMargin'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'recentActivities'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
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
        // method 'profitMarginChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recentActivitiesChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        case 6: _t->profitMarginChanged(); break;
        case 7: _t->recentActivitiesChanged(); break;
        case 8: _t->refresh(); break;
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
            if (_t _q_method = &UserDashboard::profitMarginChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (UserDashboard::*)();
            if (_t _q_method = &UserDashboard::recentActivitiesChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
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
        case 5: *reinterpret_cast< double*>(_v) = _t->profitMargin(); break;
        case 6: *reinterpret_cast< QVariantList*>(_v) = _t->recentActivities(); break;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
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
void UserDashboard::profitMarginChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void UserDashboard::recentActivitiesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
