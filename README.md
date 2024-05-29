JTTP 1/0.1 
# Johnray Tiny Transfer Protocol

# Simple HTTP Server

This is a HTTP server written in C. It listens on port 80 and serves an HTML file or any other resources in the root location to clients upon request.

## Usage

1. Clone this repository.
2. Compile the code using `gcc`:
    ```
    gcc -o http_server http_server.c
    ```
3. Run the compiled executable:
    ```
    ./http_server
    ```
4. Open a web browser and navigate to `http://localhost` to see the served HTML content.

## Features

- Listens on port 80 by default.
- Serves a basic HTML file to clients.
- Handles multiple client connections using socket programming.
- Uses the MIT License.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

## License

This project is licensed under the terms of the MIT License. See the [LICENSE](LICENSE) file for details.
