import random, scipy.misc, os, re

indexs = set()

def find_subset(index, n, k):
    p = 1
    for i, j in zip(range(n, n - k, -1), range(1, k + 1)):
        p *= i
        p //= j
    q = p
    for k in range(k, 0, -1):
        p *= k
        p //= n
        while q - p > index:
            q -= p
            p *= (n - k)
            p -= p % k
            n -= 1
            p //= n
        n -= 1
        yield n


def select_subset(n):
    while True:
        num = random.randrange(pow(2, n))
        if num not in indexs:
            indexs.add(num)
            break
    k = 0
    k_n = scipy.misc.comb(n, k, exact=True)
    while num - k_n >= 0:
        num -= k_n
        k += 1
        k_n = scipy.misc.comb(n, k, exact=True)
    return k, num


def output(F, filename, n, m):
    with open(filename, 'w') as output:
        output.write('p cnf %d %d\n' % (n, m))
        for subset in F:
            for element in subset: output.write('%d ' % (element + 1))
            output.write('0\n')
        for subset in F:
            for element in subset: output.write('%d ' % -(element + 1))
            output.write('0\n')


def run_minisat(instances):
    for instance in instances:
        result = os.popen('./minisat instance/%s out/%s' % (instance, instance)).read().strip()
        sat = result.split('\n')[-1].lstrip()
        cpu_time = re.search('CPU.*?:(.*)? *s', result).group(1)
        print(instance, sat, cpu_time)



def generate_instances(n, m):
    indexs.clear()
    instances = []
    for t in range(10):
        while True:
            F = []
            for i in range(m):
                while True:
                    k, index = select_subset(n)
                    if k > 1: break
                subset = list(find_subset(index, n, k))[::-1]
                F.append(subset)
            S = set()
            for subset in F:
                S = S | set(subset)
            if len(S) == n: break
        filename = '%05d-%d' % (n, t)
        instances.append(filename)
        output(F, 'instance/%s' % filename, n, m * 2)
    return instances


if __name__ == '__main__':
    m = 100000
    instances = []
    for n in range(20, 41, 1): instances.extend(generate_instances(n, m))
    run_minisat(instances)
