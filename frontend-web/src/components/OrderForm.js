import React, { useState } from 'react';
import { createOrder } from '../services/api';

function OrderForm(props) {
  var onOrderCreated = props.onOrderCreated;

  var [customerName, setCustomerName] = useState('');
  var [customerPhone, setCustomerPhone] = useState('');
  var [deliveryAddress, setDeliveryAddress] = useState('');
  var [storeName, setStoreName] = useState('');
  var [menuItems, setMenuItems] = useState('');
  var [totalPrice, setTotalPrice] = useState('');

  function handleSubmit(e) {
    e.preventDefault();

    var order = {
      customerName: customerName,
      customerPhone: customerPhone,
      deliveryAddress: deliveryAddress,
      storeName: storeName,
      menuItems: menuItems,
      totalPrice: parseInt(totalPrice)
    };

    createOrder(order).then(function() {
      setCustomerName('');
      setCustomerPhone('');
      setDeliveryAddress('');
      setStoreName('');
      setMenuItems('');
      setTotalPrice('');
      onOrderCreated();
    }).catch(function(err) {
      alert('주문 생성 실패');
      console.log(err);
    });
  }

  return (
    <div>
      <h2>새 주문</h2>
      <form onSubmit={handleSubmit}>
        <div>
          <label>고객명</label>
          <input type="text" value={customerName} onChange={e => setCustomerName(e.target.value)} />
        </div>
        <div>
          <label>연락처</label>
          <input type="text" value={customerPhone} onChange={e => setCustomerPhone(e.target.value)} />
        </div>
        <div>
          <label>배달 주소</label>
          <input type="text" value={deliveryAddress} onChange={e => setDeliveryAddress(e.target.value)} />
        </div>
        <div>
          <label>가맹점</label>
          <input type="text" value={storeName} onChange={e => setStoreName(e.target.value)} />
        </div>
        <div>
          <label>메뉴</label>
          <input type="text" value={menuItems} onChange={e => setMenuItems(e.target.value)} />
        </div>
        <div>
          <label>금액</label>
          <input type="number" value={totalPrice} onChange={e => setTotalPrice(e.target.value)} />
        </div>
        <button type="submit">주문 등록</button>
      </form>
    </div>
  );
}

export default OrderForm;
