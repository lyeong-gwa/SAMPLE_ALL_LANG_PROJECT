import React from 'react';
import { updateOrderStatus } from '../services/api';

function OrderList(props) {
  var orders = props.orders;
  var onStatusChange = props.onStatusChange;

  function handleStatusChange(id, status) {
    updateOrderStatus(id, status).then(function() {
      onStatusChange();
    });
  }

  function getStatusColor(status) {
    if (status ==="PENDING") return "orange";
    if (status ==="CONFIRMED") return "blue";
    if (status ==="DELIVERING") return "green";
    if (status ==="COMPLETED") return "gray";
    if (status ==="CANCELLED") return "red";
    return "black";
  }

  function formatPrice(price) {
    return price.toString().replace(/\B(?=(\d{3})+(?!\d))/g, ",") + "원";
  }

  return (
    <div>
      <h2>주문 목록</h2>
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>고객명</th>
            <th>가맹점</th>
            <th>메뉴</th>
            <th>금액</th>
            <th>상태</th>
            <th>액션</th>
          </tr>
        </thead>
        <tbody>
          {orders.map(function(order) {
            return (
              <tr key={order.id}>
                <td>{order.id}</td>
                <td>{order.customerName}</td>
                <td>{order.storeName}</td>
                <td>{order.menuItems}</td>
                <td>{formatPrice(order.totalPrice)}</td>
                <td style={{color: getStatusColor(order.status)}}>{order.status}</td>
                <td>
                  <button onClick={() => handleStatusChange(order.id, 'CONFIRMED')}>확인</button>
                  <button onClick={() => handleStatusChange(order.id, 'DELIVERING')}>배달중</button>
                  <button onClick={() => handleStatusChange(order.id, 'COMPLETED')}>완료</button>
                </td>
              </tr>
            );
          })}
        </tbody>
      </table>
    </div>
  );
}

export default OrderList;
