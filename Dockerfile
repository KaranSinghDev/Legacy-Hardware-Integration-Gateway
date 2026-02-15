# --- Stage 1: Build Environment ---
FROM almalinux:9 AS builder

RUN dnf install -y gcc-c++ cmake make git findutils && dnf clean all

WORKDIR /build_dir
COPY . .

RUN mkdir build && cd build && \
    cmake .. && \
    cmake --build .

# --- Stage 2: Runtime Environment ---
FROM almalinux:9
RUN dnf install -y libstdc++ && dnf clean all
WORKDIR /app
COPY --from=builder /build_dir/build/lhig_gw .
CMD ["./lhig_gw"]