import sys
import os

def copy_file(source, destination):
    try:
        # Open the source file for reading
        with open(source, 'rb') as src_file:
            # Check if the destination file already exists
            if os.path.exists(destination):
                response = input(f"Destination file '{destination}' already exists. Overwrite? (y/n): ")
                if response.lower() != 'y':
                    print("Operation aborted.")
                    return
            
            # Open the destination file for writing
            with open(destination, 'wb') as dest_file:
                # Read and write in chunks
                while chunk := src_file.read(1024):
                    dest_file.write(chunk)
        
        print(f"File '{source}' copied to '{destination}' successfully.")
    
    except FileNotFoundError:
        print(f"Error: The file '{source}' does not exist.")
    except IOError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <source file> <destination file>")
        sys.exit(1)

    source = sys.argv[1]
    destination = sys.argv[2]

    copy_file(source, destination)

if __name__ == "__main__":
    main()