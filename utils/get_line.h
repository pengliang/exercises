#ifndef K_AND_R_ASSIGNMENTS_UTILS_GET_LINE_H_
#define K_AND_R_ASSIGNMENTS_UTILS_GET_LINE_H_

// Reads a limited length line from the standard input.
// If the user's input is ended with line-feed '\n',
// the line feed character is also included in the output.
//
// @param line_buf[] the buffer to store the user's input
// @param line_buf_length the maximum length of the buffer
// @return the length of the user's input
int GetLimitedLine(char line_buf[], int line_buf_length);

// Reads a line from the standard input.
// If the length of user's input is > line_buf_length,
// the buffer will be reallocated with 2 * line_buf_length auto.
// All the line will be ended with '\0'.
//
// Note: The buffer's address may be changed.
//
// @param line_buf_point the address of the pointer to the buffer.
// @param line_buf_length the initial length of the buffer.
// @return the length of the user's input.
int GetLine(char **line_buf_point, int line_buf_length);

// Reads multiple lines from input.
// If the user's input is ended with line-feed '\n',
// the line feed character is also included in the buffer.
// All the line will be terminated with '\0'.
//
// @param line_ptr the buffer to store the pointer of line
// @param max_lines the max number of lines can be read
// @return the number of lines read from input or
//         -1 for too many lines input or
//         -2 for memory overflow
int GetLines(char *line_ptr[], int max_lines);

#endif  // K_AND_R_ASSIGNMENTS_UTILS_GET_LINE_H_
