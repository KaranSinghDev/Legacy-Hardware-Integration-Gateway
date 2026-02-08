# --- Stage 1: Build Environment ---
FROM almalinux:9 AS builder

# Install build dependencies
RUN dnf install -y \
    gcc-c++ \
    cmake \
    make \
    git \
    && dnf clean all

# Set working directory
WORKDIR /build_dir

# Copy source code
COPY . .

# Build the application
RUN mkdir build && cd build && \
    cmake .. && \
    cmake --build .

# --- Stage 2: Runtime Environment ---
FROM almalinux:9

# Install runtime dependencies (if any)
RUN dnf install -y libstdc++ && dnf clean all

WORKDIR /app

# Copy only the compiled binary from the builder stage
COPY --from=builder /build_dir/build/lhig_gw .

# Entry point
CMD ["./lhig_gw"]