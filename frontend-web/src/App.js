import React, { useState, useEffect } from 'react';
import OrderList from './components/OrderList';
import OrderForm from './components/OrderForm';
import { getOrders } from './services/api';

function App() {
  var orders = [];
  var setOrders = null;

  [orders, setOrders] = useState([]);

  useEffect(() => {
    loadOrders();
  }, []);

  function loadOrders() {
    getOrders().then(function(response) {
      setOrders(response.data);
    }).catch(function(error) {
      console.log(error);
    });
  }

  return (
    <div className="App">
      <h1>DeliveryHub 주문 관리</h1>
      <OrderForm onOrderCreated={loadOrders} />
      <OrderList orders={orders} onStatusChange={loadOrders} />
    </div>
  );
}

export default App;
