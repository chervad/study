import ReactTable from "react-table";
import 'react-table/react-table.css';
import React, { Component } from 'react';
import './App.css';

class App extends Component {
  constructor(props) {
    super(props);
    this.state = { 
      keywords : '', data : []
    };
  }

  fetchData = () => {
    const url = `https://api.github.com/search/repositories?q=${this.state.keyword}`;
    fetch(url)
    .then(response => response.json())
    .then(responseData => {
      this.setState({ data : responseData.items });
    });
  }

  handleChange = (e) => {
    this.setState({ keyword : e.target.value });
  }

  render() {
    const columns = [{
      Header: 'Name',
      accessor: 'full_name'
    }, {
      Header: 'URL',
      accessor: 'html_url'
    }, {
      Header: 'Owner',
      accessor: 'owner.login'
    }, {
      id: 'button',
      sortable: false,
      filterable: false,
      width: 100,
      accessor: 'full_name',
      Cell: ({value}) => (<button className="btn btn-default btn-link" onClick={() => {this.btnClick(value)}}>Press me</button>)
    }]
    return (
      <div className="App">
        <input type="text" onChange={this.handleChange} />
        <button onClick={this.fetchData} value={this.state.keywords} >Fetch</button>
        <ReactTable 
          data={this.state.data} 
          columns={columns} 
          filterable={true}
          defaultPageSize={10}
        />
      </div>
    );
  }

}

export default App;
