 __thread int tls_initial_a = 0x55;

static __thread int tls_local_a = 0x66;
static __thread int tls_local_b = 0x66;


int get_value()
{
    int total;
    total = tls_local_a;
    total += tls_local_b;

    return total;
}