#ifndef CONNECTION_H
#define CONNECTION_H

class Connection {
public:
    int start_id;
    int stop_id;
    int pipe_id;

    Connection(int start_id, int stop_id, int pipe_id);
};

#endif // CONNECTION_H