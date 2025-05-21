FROM gcc:13

WORKDIR /app

# Copy files
COPY . .

# Build your project using CMake
RUN apt update && apt install -y cmake
RUN mkdir build && cd build && cmake .. && make

# Expose TCP port
EXPOSE 8080

# Start the server
CMD ["./build/cache_server"]
