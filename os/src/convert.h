#ifndef CONVERT_H
#define CONVERT_H
 
void int_to_str(uint32_t num, char *str) {
    int i = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    str[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}
 
void ull_to_str(unsigned long long value, char *buf) {
    char temp[21];
    int i = 0;
 
    if (value == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
 
    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }
 
    int j = 0;
    while (i > 0) {
        buf[j++] = temp[--i];
    }
    buf[j] = '\0';
}
 
int str_to_int(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;
 
    while (str[i] == ' ') {
        i++;
    }
 
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
 
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
 
    return result * sign;
}

void fixed_to_str(long long value, char *buf) {
    int negative = 0;
    if (value < 0) {
        negative = 1;
        value = -value;
    }
 
    long long whole = value / 1000;
    long long frac = value % 1000;
 
    int i = 0;
    if (negative) {
        buf[i++] = '-';
    }
 
    char whole_buf[21];
    int_to_str((uint32_t)whole, whole_buf);
 
    int j = 0;
    while (whole_buf[j] != '\0') {
        buf[i++] = whole_buf[j++];
    }
 
    buf[i++] = '.';
 
    char frac_buf[4];
    frac_buf[0] = '0' + (char)(frac / 100);
    frac_buf[1] = '0' + (char)((frac / 10) % 10);
    frac_buf[2] = '0' + (char)(frac % 10);
    frac_buf[3] = '\0';
 
    j = 0;
    while (frac_buf[j] != '\0') {
        buf[i++] = frac_buf[j++];
    }
 
    buf[i] = '\0';
}

long long str_to_float(const char *str) {
    int sign = 1;
    int i = 0;
 
    while (str[i] == ' ') {
        i++;
    }
 
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
 
    long long whole = 0;
    while (str[i] >= '0' && str[i] <= '9') {
        whole = whole * 10 + (str[i] - '0');
        i++;
    }
 
    long long frac = 0;
    if (str[i] == '.') {
        i++;
 
        int place = 100;
        int digits = 0;
        while (str[i] >= '0' && str[i] <= '9' && digits < 3) {
            frac += (str[i] - '0') * place;
            place /= 10;
            i++;
            digits++;
        }
        while (str[i] >= '0' && str[i] <= '9') {
            i++;
        }
    }
 
    return (whole * 1000 + frac) * sign;
}
 
#endif
