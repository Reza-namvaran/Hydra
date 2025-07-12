# A Minimal HTTP Server in C

Hydra is a lightweight HTTP server built in C from scratch, using raw sockets.
It supports basic HTTP GET requests, simple routing, and integration testing.

## Build Instructions

```bash
git clone https://github.com/reza-namvaran/Hydra.git
cd Hydra
cmake -S . -B build
cd build && make
```

## Usage

Start the server

```bash
./bin/Hydra
```
Server will listen on port 8080.

Now you can Test using curl

```bash
curl http://localhost:8080/
curl http://localhost:8080/hello
curl http://localhost:8080/unknown
```

or you can use client test

```bash
./bin/client_test
```

Expected output:
```plaintext
Test 1: Root Path (/) ... PASS
Test 2: Hello Path (/hello) ... PASS
Test 3: Nonexistent Path (/not_exist) ... PASS

3/3 tests passed.

```