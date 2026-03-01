import pytest
import asyncio
import time
from asyncua import Client, ua

# --- Configuration ---
GATEWAY_URL = "opc.tcp://localhost:4840"
VOLTAGE_NODE_ID = "ns=1;s=Voltage"

# This is the simplest and most reliable async fixture pattern
@pytest.fixture(scope="module")
async def client():
    """Connects to the OPC UA server once per test module."""
    async with Client(url=GATEWAY_URL) as client:
        print("\n[Fixture] Client connected.")
        yield client
    print("\n[Fixture] Client disconnected.")

@pytest.mark.asyncio
async def test_connectivity(client):
    """Test 1: Can we connect and find the Voltage node?"""
    print("\n--- Running Connectivity Test ---")
    voltage_node = client.get_node(VOLTAGE_NODE_ID)
    value = await voltage_node.get_value()
    print(f"Successfully read initial value: {value}")
    assert isinstance(value, float)
    print("✅ Connectivity Test Passed")

@pytest.mark.asyncio
async def test_data_integrity_and_latency(client):
    """Test 2: Is the data updated, and how fast?"""
    print("\n--- Running Data Integrity & Latency Test ---")
    voltage_node = client.get_node(VOLTAGE_NODE_ID)
    
    initial_val = await voltage_node.get_value()
    print(f"Initial Voltage: {initial_val:.4f} V")
    
    await asyncio.sleep(2.5)
    
    start_time = time.monotonic()
    updated_val = await voltage_node.get_value()
    end_time = time.monotonic()
    
    latency_ms = (end_time - start_time) * 1000
    
    print(f"Updated Voltage: {updated_val:.4f} V")
    print(f"OPC UA Read Latency: {latency_ms:.2f} ms")
    
    assert initial_val != updated_val, "Voltage value was not updated!"
    assert latency_ms < 100, "Read latency is too high!"
    print("✅ Data Integrity & Latency Test Passed")

@pytest.mark.asyncio
async def test_throughput(client):
    """Test 3: How many reads can we perform in a short burst?"""
    print("\n--- Running Throughput Test ---")
    voltage_node = client.get_node(VOLTAGE_NODE_ID)
    
    num_reads = 100
    print(f"Performing {num_reads} concurrent reads...")
    
    start_time = time.monotonic()
    tasks = [voltage_node.get_value() for _ in range(num_reads)]
    await asyncio.gather(*tasks)
    end_time = time.monotonic()
    
    duration = end_time - start_time
    reads_per_sec = num_reads / duration
    
    print(f"Completed {num_reads} reads in {duration:.2f} seconds")
    print(f"Throughput: {reads_per_sec:.2f} reads/sec")
    
    assert reads_per_sec > 200, "Read throughput is below minimum!"
    print("✅ Throughput Test Passed")

@pytest.mark.skip(reason="C++ Gateway does not yet support Status/JSON nodes")
@pytest.mark.asyncio
async def test_complex_data(client):
    pass