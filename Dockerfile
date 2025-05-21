FROM archlinux:latest

# Install build tools and dependencies
RUN pacman -Syu --noconfirm && \
    pacman -S --noconfirm cmake gcc make base-devel

# Copy project files
WORKDIR /app
COPY . .

# Build the C++ server
RUN cmake -Bbuild -H. && \
    cmake --build build

# Expose the port your app listens on
EXPOSE 8080

# Run the server
CMD ["./build/cache_server"]
