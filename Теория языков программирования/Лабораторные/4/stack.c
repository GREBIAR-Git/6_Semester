typedef int T;
typedef struct Node_tag {
    T value;
    struct Node_tag* next;
} Node_t;

void push(Node_t** head, T value) {
    Node_t* tmp = malloc(sizeof(Node_t));
    if (tmp == NULL) {
        exit(STACK_OVERFLOW);
    }
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}

Node_t* pop1(Node_t** head) {
    Node_t* out;
    if ((*head) == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    return out;
}

T pop2(Node_t** head) {
    Node_t* out;
    T value;
    if (*head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}

T peek(const Node_t* head) {
    if (head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    return head->value;
}

///Node_t *head = NULL;