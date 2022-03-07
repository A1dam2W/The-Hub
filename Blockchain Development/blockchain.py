"""
@author: adam.wang
"""
import datetime
import hashlib
import json
from flask import Flask, jsonify

class Blockchain:
    
    def __init__(self):
        self.chain = []
        self.create_block(proof = 1, previous_hash = '0')
        
        
    def create_block(self, proof, previous_hash):
        block = {'index': len(self.chain)+1, 
                 'timestamp': str(datetime.datetime.now()), 
                 'proof': proof, 
                 'previous_hash': previous_hash}
        self.chain.append(block)
        return block
    
    def get_prev(self):
        return self.chain[-1]
    
    def certification(self, previous_proof):
        new_proof = 1
        check_proof = False
        while check_proof is False:
            hash_operation = hashlib.sha256(str(new_proof**7 - 
                    (previous_proof-1)**3).encode()).hexdigest()
            
            if hash_operation[:4] == '0000':
                check_proof = True
            else:
                new_proof += 1               
        return new_proof
    
    def hash(self, block):
        encoded_block = json.dumps(block, sort_keys = True).encode()
        return hashlib.sha256(encoded_block).hexdigest()
    
    def isChainValid(self, chain):
        previous_block = chain[0]
        block_index = 1
        while block_index < len(chain):
            curr = chain[block_index]
            if curr['previous_hash'] != self.hash(previous_block):
                return False
            previous_proof = previous_block['proof']
            proof = curr['proof']
            hash_operation = hashlib.sha256(str(proof**7 - 
                    (previous_proof-1)**3).encode()).hexdigest()
            if hash_operation[:4] != '0000':
                return False
            previous_block = curr
            block_index += 1
        return True
            
#Create Web App
app = Flask(__name__)
app.config['JSONIFY_PRETTYPRINT_REGULAR'] = False

#Create Blockchain
blockchain = Blockchain()

#Mining a New Block
@app.route('/mine_block', methods = ['GET'])

def mine_block():
    previous_block = blockchain.get_prev()
    previous_proof = previous_block['proof']
    proof = blockchain.certification(previous_proof)
    previous_hash = blockchain.hash(previous_block)
    block = blockchain.create_block(proof, previous_hash)
    response = {'message':'Congrats! You nailed it!',
                'index': block['index'],
                'timestamp': block['timestamp'],
                'proof': block['proof'],
                'previous_hash': block['previous_hash']}
    return jsonify(response),200     
            
#Getting the full Blockchain            
@app.route('/get_chain', methods = ['GET'])

def get_chain():
    response = {'chain': blockchain.chain,
                'length': len(blockchain.chain)}        
    return jsonify(response),200       


#Running the app
app.run(host = '0.0.0.0', port = 5001)           
            
            
            
            
            
            
            
            
            
            
            
            
            