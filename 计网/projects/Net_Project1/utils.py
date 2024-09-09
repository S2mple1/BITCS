import logging
from datetime import datetime


def read_config(config_file):
    config = {}
    with open(config_file, 'r', encoding='utf-8') as file:
        for line in file:
            if line.startswith('#') or not line.strip():
                continue
            key, value = line.strip().split('=')
            config[key.strip()] = value.strip()
    return config


def setup_logger(type):
    logger = logging.getLogger('file_transfer')
    logger.setLevel(logging.DEBUG)

    fh = logging.FileHandler(f'{type}_{datetime.now().strftime("%Y%m%d%H%M%S")}.log')
    fh.setLevel(logging.DEBUG)

    formatter = logging.Formatter('%(asctime)s - %(message)s')
    fh.setFormatter(formatter)

    logger.addHandler(fh)

    return logger
