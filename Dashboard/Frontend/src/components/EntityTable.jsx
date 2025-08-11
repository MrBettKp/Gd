import React from 'react';

export default function EntityTable({ entities }) {
  return (
    <div className="entity-table">
      <h2>Entity List</h2>
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>Type</th>
            <th>X</th>
            <th>Y</th>
            <th>Z</th>
            <th>Health</th>
          </tr>
        </thead>
        <tbody>
          {entities.map(entity => (
            <tr key={entity.id}>
              <td>{entity.id}</td>
              <td>{entity.type}</td>
              <td>{entity.x.toFixed(2)}</td>
              <td>{entity.y.toFixed(2)}</td>
              <td>{entity.z.toFixed(2)}</td>
              <td>{entity.health || 'N/A'}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}
