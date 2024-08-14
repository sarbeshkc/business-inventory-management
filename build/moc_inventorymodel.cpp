/****************************************************************************
** Meta object code from reading C++ file 'inventorymodel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inventorymodel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inventorymodel.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSInventoryModelENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSInventoryModelENDCLASS = QtMocHelpers::stringData(
    "InventoryModel",
    "errorOccurred",
    "",
    "error",
    "totalItemsChanged",
    "lowStockItemsChanged",
    "totalCostChanged",
    "lowStockNotificationsChanged",
    "categoriesChanged",
    "topItemsChanged",
    "addItem",
    "name",
    "category",
    "quantity",
    "price",
    "updateItem",
    "id",
    "deleteItem",
    "searchItems",
    "searchText",
    "sortItems",
    "column",
    "Qt::SortOrder",
    "order",
    "refresh",
    "refreshAnalytics",
    "getItemDetails",
    "itemId",
    "totalItems",
    "lowStockItems",
    "totalCost",
    "lowStockNotifications",
    "categories",
    "topItems"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSInventoryModelENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       6,  149, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  104,    2, 0x06,    7 /* Public */,
       4,    0,  107,    2, 0x06,    9 /* Public */,
       5,    0,  108,    2, 0x06,   10 /* Public */,
       6,    0,  109,    2, 0x06,   11 /* Public */,
       7,    0,  110,    2, 0x06,   12 /* Public */,
       8,    0,  111,    2, 0x06,   13 /* Public */,
       9,    0,  112,    2, 0x06,   14 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      10,    4,  113,    2, 0x02,   15 /* Public */,
      15,    5,  122,    2, 0x02,   20 /* Public */,
      17,    1,  133,    2, 0x02,   26 /* Public */,
      18,    1,  136,    2, 0x02,   28 /* Public */,
      20,    2,  139,    2, 0x02,   30 /* Public */,
      24,    0,  144,    2, 0x02,   33 /* Public */,
      25,    0,  145,    2, 0x02,   34 /* Public */,
      26,    1,  146,    2, 0x102,   35 /* Public | MethodIsConst  */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Double,   11,   12,   13,   14,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Double,   16,   11,   12,   13,   14,
    QMetaType::Bool, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 22,   21,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QVariantMap, QMetaType::Int,   27,

 // properties: name, type, flags
      28, QMetaType::Int, 0x00015001, uint(1), 0,
      29, QMetaType::Int, 0x00015001, uint(2), 0,
      30, QMetaType::Double, 0x00015001, uint(3), 0,
      31, QMetaType::QStringList, 0x00015001, uint(4), 0,
      32, QMetaType::QStringList, 0x00015001, uint(5), 0,
      33, QMetaType::QVariantList, 0x00015001, uint(6), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject InventoryModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_CLASSInventoryModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSInventoryModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSInventoryModelENDCLASS_t,
        // property 'totalItems'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'lowStockItems'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'totalCost'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'lowStockNotifications'
        QtPrivate::TypeAndForceComplete<QStringList, std::true_type>,
        // property 'categories'
        QtPrivate::TypeAndForceComplete<QStringList, std::true_type>,
        // property 'topItems'
        QtPrivate::TypeAndForceComplete<QVariantList, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<InventoryModel, std::true_type>,
        // method 'errorOccurred'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'totalItemsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lowStockItemsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'totalCostChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'lowStockNotificationsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'categoriesChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'topItemsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addItem'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'updateItem'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'deleteItem'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'searchItems'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'sortItems'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::SortOrder, std::false_type>,
        // method 'refresh'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refreshAnalytics'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getItemDetails'
        QtPrivate::TypeAndForceComplete<QVariantMap, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void InventoryModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InventoryModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->errorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->totalItemsChanged(); break;
        case 2: _t->lowStockItemsChanged(); break;
        case 3: _t->totalCostChanged(); break;
        case 4: _t->lowStockNotificationsChanged(); break;
        case 5: _t->categoriesChanged(); break;
        case 6: _t->topItemsChanged(); break;
        case 7: { bool _r = _t->addItem((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: { bool _r = _t->updateItem((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->deleteItem((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->searchItems((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->sortItems((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<Qt::SortOrder>>(_a[2]))); break;
        case 12: _t->refresh(); break;
        case 13: _t->refreshAnalytics(); break;
        case 14: { QVariantMap _r = _t->getItemDetails((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (InventoryModel::*)(const QString & );
            if (_t _q_method = &InventoryModel::errorOccurred; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InventoryModel::*)();
            if (_t _q_method = &InventoryModel::totalItemsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (InventoryModel::*)();
            if (_t _q_method = &InventoryModel::lowStockItemsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (InventoryModel::*)();
            if (_t _q_method = &InventoryModel::totalCostChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (InventoryModel::*)();
            if (_t _q_method = &InventoryModel::lowStockNotificationsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (InventoryModel::*)();
            if (_t _q_method = &InventoryModel::categoriesChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (InventoryModel::*)();
            if (_t _q_method = &InventoryModel::topItemsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<InventoryModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->totalItems(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->lowStockItems(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->totalCost(); break;
        case 3: *reinterpret_cast< QStringList*>(_v) = _t->lowStockNotifications(); break;
        case 4: *reinterpret_cast< QStringList*>(_v) = _t->categories(); break;
        case 5: *reinterpret_cast< QVariantList*>(_v) = _t->topItems(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *InventoryModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InventoryModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSInventoryModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int InventoryModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
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
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void InventoryModel::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InventoryModel::totalItemsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void InventoryModel::lowStockItemsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void InventoryModel::totalCostChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void InventoryModel::lowStockNotificationsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void InventoryModel::categoriesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void InventoryModel::topItemsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
