#include "object.h"


// Object::Object(std::variant<Item, Chest> obj, size_t x, size_t y) : _object(std::move(obj)), _x(x), _y(y) {
//     std::visit([this](auto& o) {
//         _name = o.name;
//     }, _object);
// }

Object::Object(Item obj, size_t x, size_t y) : _object(obj), _x(x), _y(y) {
    _name = obj.name;
}
