#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "table.h"
#include "btree.h"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
    StatementType type;
    Row row_to_insert;  // Only used for insert statements
} Statement;

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

void print_prompt() {
    printf("db > ");
}

void read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read = getline(&input_buffer->buffer, &input_buffer->buffer_length, stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = '\0';
}

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement) {
    statement->type = STATEMENT_INSERT;

    char* keyword = strtok(input_buffer->buffer, " ");
    char* id_string = strtok(NULL, " ");
    char* username = strtok(NULL, " ");
    char* email = strtok(NULL, " ");

    if (id_string == NULL || username == NULL || email == NULL) {
        return PREPARE_UNRECOGNIZED_STATEMENT;
    }

    statement->row_to_insert.id = atoi(id_string);
    strncpy(statement->row_to_insert.username, username, COLUMN_USERNAME_SIZE);
    strncpy(statement->row_to_insert.email, email, COLUMN_EMAIL_SIZE);

    return PREPARE_SUCCESS;
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        return prepare_insert(input_buffer, statement);
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement, Table* table) {
    switch (statement->type) {
        case STATEMENT_INSERT:
            if (table->row_count >= TABLE_MAX_ROWS) {
                printf("Error: Table full.\n");
                return;
            }
            table->rows[table->row_count] = statement->row_to_insert;
            table->row_count++;
            printf("Inserted.\n");
            break;
        case STATEMENT_SELECT:
            for (size_t i = 0; i < table->row_count; i++) {
                Row* row = &table->rows[i];
                printf("(%d, %s, %s)\n", row->id, row->username, row->email);
            }
            break;
    }
}

void repl(void) {
    Table table = {.row_count = 0};
    InputBuffer* input_buffer = new_input_buffer();

    while (true) {
        print_prompt();
        read_input(input_buffer);
        if (input_buffer->buffer[0] == '.') {
            if (strcmp(input_buffer->buffer, ".exit") == 0) {
                close_input_buffer(input_buffer);
                exit(EXIT_SUCCESS);
            } else {
                printf("Unrecognized command '%s'\n", input_buffer->buffer);
                continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }
        execute_statement(&statement, &table);
    }
}
