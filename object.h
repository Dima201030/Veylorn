enum ObjectType {
    EMPTY = 0,
    WALL,
    CHEST,
    ITEM
};

struct object {
    ObjectType type;

    int x;
    int y;
};
