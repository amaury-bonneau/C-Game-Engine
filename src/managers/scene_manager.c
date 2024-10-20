#include "../components/entity.h"
#include "../components/transform_component.h"

typedef struct Node
{
    struct Node* parent;        // Parent node in the hierarchy
    struct Node* children;      // List of child nodes (can be dynamic array or linked list)
    int childCount;

    TransformComponent* transform;  // Component for position, rotation, scaling
    Entity* entity;                 // The ECS entity that corresponds to this node
} Node;

