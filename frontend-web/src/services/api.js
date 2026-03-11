import axios from 'axios';

const API_BASE_URL = process.env.REACT_APP_API_BASE_URL || "http://localhost:8080/api";
const API_KEY = process.env.REACT_APP_API_KEY || "";

var apiClient = axios.create({
  baseURL: API_BASE_URL,
  headers: {
    'Content-Type': 'application/json',
    'X-API-Key': API_KEY
  }
});

export function getOrders() {
  return apiClient.get('/orders');
}

export function getOrderById(id) {
  return apiClient.get('/orders/' + id);
}

export function createOrder(order) {
  return apiClient.post('/orders', order);
}

export function updateOrderStatus(id, status) {
  return apiClient.put('/orders/' + id + '/status?status=' + status);
}

export function searchOrders(keyword) {
  return apiClient.get('/orders/search?keyword=' + keyword);
}

export function deleteOrder(id) {
  return apiClient.delete('/orders/' + id);
}
