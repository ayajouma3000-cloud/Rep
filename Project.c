#include <stdio.h>
#include <string.h>

#define SIZE 5

typedef struct {
    char data[SIZE][50];
    int front;
    int rear;
} CircularBuffer;

// تهيئة
void init(CircularBuffer *cb) {
    cb->front = -1;
    cb->rear = -1;
}

// تحقق فارغ
int isEmpty(CircularBuffer *cb) {
    return cb->front == -1;
}

// تحقق ممتلئ
int isFull(CircularBuffer *cb) {
    return (cb->rear + 1) % SIZE == cb->front;
}

// إدخال
void enqueue(CircularBuffer *cb, char value[]) {
    if (isFull(cb)) {
        printf("Overflow! Buffer is full.\n");
        return;
    }

    if (isEmpty(cb)) {
        cb->front = 0;
    }

    cb->rear = (cb->rear + 1) % SIZE;
    strcpy(cb->data[cb->rear], value);

    printf("Inserted: %s\n", value);
}

// إزالة
void dequeue(CircularBuffer *cb, char result[]) {
    if (isEmpty(cb)) {
        printf("Underflow! Buffer is empty.\n");
        return;
    }

    strcpy(result, cb->data[cb->front]);

    if (cb->front == cb->rear) {
        cb->front = cb->rear = -1;
    } else {
        cb->front = (cb->front + 1) % SIZE;
    }
}

// عرض
void display(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer is empty\n");
        return;
    }

    int i = cb->front;
    printf("Buffer contents: ");

    while (1) {
        printf("%s | ", cb->data[i]);
        if (i == cb->rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

// الدالة الرئيسية
int main() {
    CircularBuffer cb;
    init(&cb);

    char name[50];
    char fullText[50];
    char removed[50];

    // إدخال الاسم
    printf("Enter your name: ");
    scanf("%s", name);

    // إضافة CE-ESY
    sprintf(fullText, "%s-CE-ESY", name);

    // إدخال للمخزن
    enqueue(&cb, fullText);

    // عرض
    printf("\nAfter insertion:\n");
    display(&cb);

    // قراءة من المخزن
    printf("\nReading from buffer:\n");
    while (!isEmpty(&cb)) {
        dequeue(&cb, removed);
        printf("Removed: %s\n", removed);
    }

    // تأكيد أنه فارغ
    printf("\nAfter removing all elements:\n");
    display(&cb);

    return 0;
}
